/*
* Virtual Gamepad Emulation Framework - Windows kernel-mode bus driver
*
* MIT License
*
* Copyright (c) 2016-2020 Nefarius Software Solutions e.U. and Contributors
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/


#pragma once



//
// FDO (bus device) context data
// 
typedef struct _FDO_DEVICE_DATA
{
    //
    // Counter of interface references
    // 
    LONG InterfaceReferenceCounter;

    //
    // Next SessionId to assign to a file handle
    // 
    LONG NextSessionId;

    //
    // Periodic timer sweeping up orphaned requests
    // 
    WDFTIMER PendingPluginRequestsCleanupTimer;

} FDO_DEVICE_DATA, *PFDO_DEVICE_DATA;

#define FDO_FIRST_SESSION_ID 100

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(FDO_DEVICE_DATA, FdoGetData)

// 
// Context data associated with file objects created by user mode applications
// 
typedef struct _FDO_FILE_DATA
{
    //
    // SessionId associated with file handle.  Used to map file handles to emulated gamepad devices
    // 
    LONG SessionId;

} FDO_FILE_DATA, *PFDO_FILE_DATA;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(FDO_FILE_DATA, FileObjectGetData)

//
// Context data for plugin requests
// 
typedef struct _FDO_PLUGIN_REQUEST_DATA
{
    //
    // Unique serial number of the device on the bus
    // 
    ULONG Serial;

    //
    // High resolution timestamp taken when this request got moved to pending state
    // 
    LARGE_INTEGER Timestamp;

    //
    // Performance counter system frequency taken upon fetching timestamp
    // 
    LARGE_INTEGER Frequency;

} FDO_PLUGIN_REQUEST_DATA, *PFDO_PLUGIN_REQUEST_DATA;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(FDO_PLUGIN_REQUEST_DATA, PluginRequestGetData)

