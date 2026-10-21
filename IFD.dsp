# Microsoft Developer Studio Project File - Name="IFD" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=IFD - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IFD.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IFD.mak" CFG="IFD - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IFD - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "IFD - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/PC_Program/PC_Protocol_OCX/IFD_VC60", LUDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IFD - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "IFD - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "IFD - Win32 Release"
# Name "IFD - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DlgDeviceSetLiveParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceSetup2.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDispenseStart.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMultiBatch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetupStateData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetupStateData2.cpp
# End Source File
# Begin Source File

SOURCE=.\IFD.cpp
# End Source File
# Begin Source File

SOURCE=.\IFD.rc
# End Source File
# Begin Source File

SOURCE=.\IFDDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\IFDView.cpp
# End Source File
# Begin Source File

SOURCE=.\ifdx_sb7.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DlgDeviceSetLiveParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceSetup2.h
# End Source File
# Begin Source File

SOURCE=.\DlgDispenseStart.h
# End Source File
# Begin Source File

SOURCE=.\DlgMultiBatch.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetupStateData.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetupStateData2.h
# End Source File
# Begin Source File

SOURCE=.\IFD.h
# End Source File
# Begin Source File

SOURCE=.\IFDDoc.h
# End Source File
# Begin Source File

SOURCE=.\IFDView.h
# End Source File
# Begin Source File

SOURCE=.\ifdx_sb7.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Connect.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DeviceAlive.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DeviceNotAlive.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Disconnect.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IFD.ico
# End Source File
# Begin Source File

SOURCE=.\res\IFD.rc2
# End Source File
# Begin Source File

SOURCE=.\res\IFDDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section IFD : {48D347FA-196E-49DB-A329-F31E43237231}
# 	2:21:DefaultSinkHeaderFile:ifdx_sb7.h
# 	2:16:DefaultSinkClass:CIFDX_SB7
# End Section
# Section IFD : {8E9E416E-AC01-42B9-8F83-939392AE56E5}
# 	2:5:Class:CIFDX_SB7
# 	2:10:HeaderFile:ifdx_sb7.h
# 	2:8:ImplFile:ifdx_sb7.cpp
# End Section
# Section IFD : {8E9E416E-AC01-42B9-8F83-939392AE56E4}
# 	2:5:Class:CIFDX
# 	2:10:HeaderFile:ifdx.h
# 	2:8:ImplFile:ifdx.cpp
# End Section
# Section IFD : {48D347FA-196E-49DB-A329-F31E43237230}
# 	2:21:DefaultSinkHeaderFile:ifdx.h
# 	2:16:DefaultSinkClass:CIFDX
# End Section
