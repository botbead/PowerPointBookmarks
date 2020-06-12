// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// $Rev: 16580 $
// File generated on 2009-11-26 13:31:11 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Common Files\Microsoft Shared\Office10\MSO.DLL (2)
// LIBID: {2DF8D04C-5BFA-101B-BDE5-00AA0044DE52}
// LCID: 0
// Helpfile: C:\Program Files\Common Files\Microsoft Shared\Office10\vbaof10.chm
// HelpString: Microsoft Office 10.0 Object Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\stdole2.tlb)
// Parent TypeLibrary:
//   (0) v2.7 PowerPoint, (G:\Program Files\Microsoft Office\Office10\MSPPT.OLB)
// Errors:
//   Hint: Symbol 'RGB' renamed to 'rgb'
//   Hint: Symbol 'RGB' renamed to 'rgb'
//   Hint: Symbol 'Update' renamed to '_Update'
//   Hint: Symbol 'Click' renamed to '_Click'
//   Hint: Symbol 'Click' renamed to '_Click'
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include "Office_TLB.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Office_tlb
{


// *********************************************************************//
// GUIDS declared in the TypeLibrary                                      
// *********************************************************************//
const GUID LIBID_Office = {0x2DF8D04C, 0x5BFA, 0x101B,{ 0xBD, 0xE5, 0x00,0xAA, 0x00, 0x44,0xDE, 0x52} };
const GUID IID_IAccessible = {0x618736E0, 0x3C3D, 0x11CF,{ 0x81, 0x0C, 0x00,0xAA, 0x00, 0x38,0x9B, 0x71} };
const GUID IID__IMsoDispObj = {0x000C0300, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID__IMsoOleAccDispObj = {0x000C0301, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID__CommandBars = {0x000C0302, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_CommandBar = {0x000C0304, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_CommandBarControls = {0x000C0306, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_CommandBarControl = {0x000C0308, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID__CommandBarButton = {0x000C030E, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_CommandBarPopup = {0x000C030A, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID__CommandBarComboBox = {0x000C030C, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID__CommandBarActiveX = {0x000C030D, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_Adjustments = {0x000C0310, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_CalloutFormat = {0x000C0311, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ColorFormat = {0x000C0312, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ConnectorFormat = {0x000C0313, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_FillFormat = {0x000C0314, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_FreeformBuilder = {0x000C0315, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_GroupShapes = {0x000C0316, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_LineFormat = {0x000C0317, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ShapeNode = {0x000C0318, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ShapeNodes = {0x000C0319, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_PictureFormat = {0x000C031A, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ShadowFormat = {0x000C031B, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_Script = {0x000C0341, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_Scripts = {0x000C0340, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_Shape = {0x000C031C, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ShapeRange = {0x000C031D, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_Shapes = {0x000C031E, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_TextEffectFormat = {0x000C031F, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_TextFrame = {0x000C0320, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ThreeDFormat = {0x000C0321, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_IMsoDispCagNotifySink = {0x000C0359, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_Balloon = {0x000C0324, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_BalloonCheckboxes = {0x000C0326, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_BalloonCheckbox = {0x000C0328, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_BalloonLabels = {0x000C032E, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_BalloonLabel = {0x000C0330, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_AnswerWizardFiles = {0x000C0361, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_AnswerWizard = {0x000C0360, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_Assistant = {0x000C0322, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_DocumentProperty = {0x2DF8D04E, 0x5BFA, 0x101B,{ 0xBD, 0xE5, 0x00,0xAA, 0x00, 0x44,0xDE, 0x52} };
const GUID IID_DocumentProperties = {0x2DF8D04D, 0x5BFA, 0x101B,{ 0xBD, 0xE5, 0x00,0xAA, 0x00, 0x44,0xDE, 0x52} };
const GUID IID_IFoundFiles = {0x000C0338, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_IFind = {0x000C0337, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_FoundFiles = {0x000C0331, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_PropertyTest = {0x000C0333, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_PropertyTests = {0x000C0334, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_FileSearch = {0x000C0332, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_COMAddIn = {0x000C033A, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_COMAddIns = {0x000C0339, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_LanguageSettings = {0x000C0353, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ICommandBarsEvents = {0x55F88892, 0x7708, 0x11D1,{ 0xAC, 0xEB, 0x00,0x60, 0x08, 0x96,0x1D, 0xA5} };
const GUID DIID__CommandBarsEvents = {0x000C0352, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID CLSID_CommandBars = {0x55F88893, 0x7708, 0x11D1,{ 0xAC, 0xEB, 0x00,0x60, 0x08, 0x96,0x1D, 0xA5} };
const GUID IID_ICommandBarComboBoxEvents = {0x55F88896, 0x7708, 0x11D1,{ 0xAC, 0xEB, 0x00,0x60, 0x08, 0x96,0x1D, 0xA5} };
const GUID DIID__CommandBarComboBoxEvents = {0x000C0354, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID CLSID_CommandBarComboBox = {0x55F88897, 0x7708, 0x11D1,{ 0xAC, 0xEB, 0x00,0x60, 0x08, 0x96,0x1D, 0xA5} };
const GUID IID_ICommandBarButtonEvents = {0x55F88890, 0x7708, 0x11D1,{ 0xAC, 0xEB, 0x00,0x60, 0x08, 0x96,0x1D, 0xA5} };
const GUID DIID__CommandBarButtonEvents = {0x000C0351, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID CLSID_CommandBarButton = {0x55F88891, 0x7708, 0x11D1,{ 0xAC, 0xEB, 0x00,0x60, 0x08, 0x96,0x1D, 0xA5} };
const GUID IID_WebPageFont = {0x000C0913, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_WebPageFonts = {0x000C0914, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_HTMLProjectItem = {0x000C0358, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_HTMLProjectItems = {0x000C0357, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_HTMLProject = {0x000C0356, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_MsoDebugOptions = {0x000C035A, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_FileDialogSelectedItems = {0x000C0363, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_FileDialogFilter = {0x000C0364, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_FileDialogFilters = {0x000C0365, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_FileDialog = {0x000C0362, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_SignatureSet = {0x000C0410, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_Signature = {0x000C0411, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_IMsoEnvelopeVB = {0x000672AC, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID DIID_IMsoEnvelopeVBEvents = {0x000672AD, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID CLSID_MsoEnvelope = {0x0006F01A, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_FileTypes = {0x000C036C, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_SearchFolders = {0x000C036A, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ScopeFolders = {0x000C0369, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ScopeFolder = {0x000C0368, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_SearchScope = {0x000C0367, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_SearchScopes = {0x000C0366, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_IMsoDiagram = {0x000C036D, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_DiagramNodes = {0x000C036E, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_DiagramNodeChildren = {0x000C036F, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_DiagramNode = {0x000C0370, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_CanvasShapes = {0x000C0371, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_OfficeDataSourceObject = {0x000C1530, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ODSOColumn = {0x000C1531, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ODSOColumns = {0x000C1532, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ODSOFilter = {0x000C1533, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ODSOFilters = {0x000C1534, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_NewFile = {0x000C0936, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_WebComponent = {0x000CD100, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_WebComponentWindowExternal = {0x000CD101, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_WebComponentFormat = {0x000CD102, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_ILicWizExternal = {0x4CAC6328, 0xB9B0, 0x11D3,{ 0x8D, 0x59, 0x00,0x50, 0x04, 0x83,0x84, 0xE3} };
const GUID IID_ILicValidator = {0x919AA22C, 0xB9AD, 0x11D3,{ 0x8D, 0x59, 0x00,0x50, 0x04, 0x83,0x84, 0xE3} };
const GUID IID_ILicAgent = {0x00194002, 0xD9C3, 0x11D3,{ 0x8D, 0x59, 0x00,0x50, 0x04, 0x83,0x84, 0xE3} };
const GUID IID_IMsoEServicesDialog = {0x000C0372, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };
const GUID IID_WebComponentProperties = {0x000C0373, 0x0000, 0x0000,{ 0xC0, 0x00, 0x00,0x00, 0x00, 0x00,0x00, 0x46} };

};     // namespace Office_tlb