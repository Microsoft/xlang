========================================================================
The Microsoft.Windows.UndockedRegFreeWinrt NuGet package
enabling you consume Windows Runtime classes registry free!
========================================================================

Installing this package will enable non-packaged desktop applications 
to leverage user-defined Windows Runtime types via the use of the 
application manifest down to RS2. 

To achieve this, the package uses the detours library, detouring RoActivateInstance, RoGetActivationFactory,
RoGetMetadataFile, and RoResolveNamespace and reimplementing the RegFree WinRT feature that is avaibale on windows version 19h1 and above. 
The package will automatically place winrtact.dll to your build folder where your exe should be.  

Initializing the detours on winrtact.dll
- Native
Initialization of the dll is taken care of automatically through ForceSymbolReferences. 

- Managed
For Managed code, one will have to initialize it manually by calling 
Microsoft.Windows.UndockedRegFreeWinrt.Initialize();
This will initialize the detours and load the catalog. 


Example application manifest:
Your application manifest should have the same name as, and be side by side to your executable.
<your_exe_name>.exe.manifest


<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0">
  <file name="TestComponent.dll">
    <activatableClass
        name="TestComponent.Class1"
        threadingModel="Both"
        xmlns="urn:schemas-microsoft-com:winrt.v1" />
    <activatableClass
        name="TestComponent.Class2"
        threadingModel="sta"
        xmlns="urn:schemas-microsoft-com:winrt.v1" />
    <activatableClass
        name="TestComponent.Class3"
        threadingModel="mta"
        xmlns="urn:schemas-microsoft-com:winrt.v1" />
  </file>
</assembly>

Starting with Windows 10 19h1, the operating system has this feature by default and will use this information directly. Be sure to  target your application for windows so that the package automatically disables itself when this feature is available by default.
https://docs.microsoft.com/en-us/windows/win32/sysinfo/targeting-your-application-at-windows-8-1

========================================================================
For more information, visit:
https://github.com/microsoft/xlang/tree/undocked_winrt_activation

For more information about using application manifests for Windows Runtime types, visit:
https://blogs.windows.com/windowsdeveloper/2019/04/30/enhancing-non-packaged-desktop-apps-using-windows-runtime-components/
========================================================================
