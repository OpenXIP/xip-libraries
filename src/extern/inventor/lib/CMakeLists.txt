# Copyright Siemens Corporate Research Inc. 2008
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(xipinv240)

if(UNIX)
  find_package(Freetype)
  find_package(JPEG)
endif(UNIX)

#--------------------------------------------------------------------
# Define the compiler flags
#
add_definitions(-DLIBRARYBUILD -D__SGIOIV_BUILD_DLL)

if(WIN32)
  add_definitions(
	  -Ddll
		-Dexceptions
		-Dshared
		-Dthread
		-Divgensources
		-Dopengl
		-DlibFL
		-Dlibimage
		-Djpeg_static
		-Diconv
		-Dfreetype
		-DWIN32
		-DINVENTOR_EXPORTS
		-DHAVE_BOOLEAN
  )
  
  #set(FREETYPE_INCLUDE_DIRS "../libFL/src")
  set(JPEG_INCLUDE_DIR "../../jpeg-6b")
endif(WIN32)

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(
  database/include
  database/src/so/nodes
  database/src/so/nodes/nurbs
  database/src/so/nodes/nurbs/head
  interaction/include
  nodekits/include
  mevis/include
  xip/include
  ${JPEG_INCLUDE_DIR}
  ${FREETYPE_INCLUDE_DIRS}
  ../libFL/src
  ../../libiconv-1.11/include)
if(WIN32)
  include_directories(
    database/src/so
    database/src/so/engines
    database/src/so/fields
    database/src/so/upgraders
    database/src/so/nodes/nurbs/clients
    database/src/so/nodes/nurbs/libnurbs
    interaction/src/draggers
    ../libFL/ang
    ../../../../include)
endif(WIN32)

if(UNIX)
  include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
endif(UNIX)

#--------------------------------------------------------------------
# Define the link directories
#
link_directories(${inventor_BINARY_DIR}/libFL)
#--------------------------------------------------------------------
# MeVis extensions to Open Inventor
#
set(HEADERS
  mevis/include/Inventor/SoCatch.h
  mevis/include/Inventor/SoInventor.h
  mevis/include/Inventor/SoMeVis.h
  mevis/include/Inventor/SoTrace.h
  mevis/include/Inventor/elements/SoGLPolygonOffsetElement.h
  mevis/include/Inventor/elements/SoGLStencilBitsElement.h
  mevis/include/Inventor/elements/SoPolygonOffsetElement.h
  mevis/include/Inventor/elements/SoStencilBitsElement.h
  mevis/include/Inventor/fields/SoSFVec2s.h
  mevis/include/Inventor/fields/SoSFVec3s.h
  mevis/include/Inventor/nodes/SoPolygonOffset.h
  mevis/include/Inventor/system/SbConfig.h
  mevis/include/Inventor/system/SbSystem.h)

set(SOURCES
  mevis/src/SoCatch.cpp
  mevis/src/SoMeVis.cpp
  mevis/src/SoTrace.cpp
  mevis/src/elements/SoGLPolygonOffsetElement.cpp
  mevis/src/elements/SoGLStencilBitsElement.cpp
  mevis/src/elements/SoPolygonOffsetElement.cpp
  mevis/src/elements/SoStencilBitsElement.cpp
  mevis/src/fields/SoSFVec2s.cpp
  mevis/src/fields/SoSFVec3s.cpp
  mevis/src/nodes/SoPolygonOffset.cpp)

if(WIN32)
  set(HEADERS ${HEADERS}
    mevis/include/SoWinEnterScope.h
    mevis/include/SoWinLeaveScope.h
    mevis/include/inttypes.h
    mevis/src/utf8_filesupport_win32.h)
	
  set(SOURCES ${SOURCES}
    mevis/src/utf8_filesupport_win32.cpp)
endif(WIN32)

#--------------------------------------------------------------------
# SGI Open Inventor 2.1.x
#
set(HEADERS ${HEADERS}
  database/include/Inventor/Sb.h
  database/include/Inventor/SbBasic.h
  database/include/Inventor/SbBox.h
  database/include/Inventor/SbColor.h
  database/include/Inventor/SbDict.h
  database/include/Inventor/SbLinear.h
  database/include/Inventor/SbPList.h
  database/include/Inventor/SbString.h
  database/include/Inventor/SbTime.h
  database/include/Inventor/SbViewportRegion.h
  database/include/Inventor/So.h
  database/include/Inventor/SoDB.h
  database/include/Inventor/SoInput.h
  database/include/Inventor/SoLists.h
  database/include/Inventor/SoOutput.h
  database/include/Inventor/SoPath.h
  database/include/Inventor/SoPickedPoint.h
  database/include/Inventor/SoPrimitiveVertex.h
  database/include/Inventor/SoType.h
  database/include/Inventor/actions/SoAction.h
  database/include/Inventor/actions/SoActions.h
  database/include/Inventor/actions/SoCallbackAction.h
  database/include/Inventor/actions/SoGLRenderAction.h
  database/include/Inventor/actions/SoGetBoundingBoxAction.h
  database/include/Inventor/actions/SoGetMatrixAction.h
  database/include/Inventor/actions/SoHandleEventAction.h
  database/include/Inventor/actions/SoPickAction.h
  database/include/Inventor/actions/SoRayPickAction.h
  database/include/Inventor/actions/SoSearchAction.h
  database/include/Inventor/actions/SoSubAction.h
  database/include/Inventor/actions/SoWriteAction.h
  database/include/Inventor/bundles/SoBundle.h
  database/include/Inventor/bundles/SoMaterialBundle.h
  database/include/Inventor/bundles/SoNormalBundle.h
  database/include/Inventor/bundles/SoTextureCoordinateBundle.h
  database/include/Inventor/caches/SoBoundingBoxCache.h
  database/include/Inventor/caches/SoCache.h
  database/include/Inventor/caches/SoGLCacheList.h
  database/include/Inventor/caches/SoGLRenderCache.h
  database/include/Inventor/caches/SoNormalCache.h
  database/include/Inventor/details/SoConeDetail.h
  database/include/Inventor/details/SoCubeDetail.h
  database/include/Inventor/details/SoCylinderDetail.h
  database/include/Inventor/details/SoDetail.h
  database/include/Inventor/details/SoDetails.h
  database/include/Inventor/details/SoFaceDetail.h
  database/include/Inventor/details/SoLineDetail.h
  database/include/Inventor/details/SoPointDetail.h
  database/include/Inventor/details/SoSubDetail.h
  database/include/Inventor/details/SoTextDetail.h
  database/include/Inventor/elements/SoAccumulatedElement.h
  database/include/Inventor/elements/SoAmbientColorElement.h
  database/include/Inventor/elements/SoBBoxModelMatrixElement.h
  database/include/Inventor/elements/SoCacheElement.h
  database/include/Inventor/elements/SoClipPlaneElement.h
  database/include/Inventor/elements/SoComplexityElement.h
  database/include/Inventor/elements/SoComplexityTypeElement.h
  database/include/Inventor/elements/SoCoordinateElement.h
  database/include/Inventor/elements/SoCreaseAngleElement.h
  database/include/Inventor/elements/SoCullVolumeElement.h
  database/include/Inventor/elements/SoCurrentGLMaterialElement.h
  database/include/Inventor/elements/SoDiffuseColorElement.h
  database/include/Inventor/elements/SoDrawStyleElement.h
  database/include/Inventor/elements/SoElement.h
  database/include/Inventor/elements/SoElements.h
  database/include/Inventor/elements/SoEmissiveColorElement.h
  database/include/Inventor/elements/SoFloatElement.h
  database/include/Inventor/elements/SoFocalDistanceElement.h
  database/include/Inventor/elements/SoFontNameElement.h
  database/include/Inventor/elements/SoFontSizeElement.h
  database/include/Inventor/elements/SoGLAmbientColorElement.h
  database/include/Inventor/elements/SoGLCacheContextElement.h
  database/include/Inventor/elements/SoGLClipPlaneElement.h
  database/include/Inventor/elements/SoGLColorIndexElement.h
  database/include/Inventor/elements/SoGLCoordinateElement.h
  database/include/Inventor/elements/SoGLDiffuseColorElement.h
  database/include/Inventor/elements/SoGLDrawStyleElement.h
  database/include/Inventor/elements/SoGLEmissiveColorElement.h
  database/include/Inventor/elements/SoGLLazyElement.h
  database/include/Inventor/elements/SoGLLightIdElement.h
  database/include/Inventor/elements/SoGLLightModelElement.h
  database/include/Inventor/elements/SoGLLinePatternElement.h
  database/include/Inventor/elements/SoGLLineWidthElement.h
  database/include/Inventor/elements/SoGLModelMatrixElement.h
  database/include/Inventor/elements/SoGLNormalElement.h
  database/include/Inventor/elements/SoGLPointSizeElement.h
  database/include/Inventor/elements/SoGLPolygonStippleElement.h
  database/include/Inventor/elements/SoGLProjectionMatrixElement.h
  database/include/Inventor/elements/SoGLRenderPassElement.h
  database/include/Inventor/elements/SoGLShapeHintsElement.h
  database/include/Inventor/elements/SoGLShininessElement.h
  database/include/Inventor/elements/SoGLSpecularColorElement.h
  database/include/Inventor/elements/SoGLTextureBlendColorElement.h
  database/include/Inventor/elements/SoGLTextureCoordinateElement.h
  database/include/Inventor/elements/SoGLTextureEnabledElement.h
  database/include/Inventor/elements/SoGLTextureImageElement.h
  database/include/Inventor/elements/SoGLTextureMatrixElement.h
  database/include/Inventor/elements/SoGLTextureModelElement.h
  database/include/Inventor/elements/SoGLTextureQualityElement.h
  database/include/Inventor/elements/SoGLTextureWrapSElement.h
  database/include/Inventor/elements/SoGLTextureWrapTElement.h
  database/include/Inventor/elements/SoGLUpdateAreaElement.h
  database/include/Inventor/elements/SoGLViewingMatrixElement.h
  database/include/Inventor/elements/SoGLViewportRegionElement.h
  database/include/Inventor/elements/SoInt32Element.h
  database/include/Inventor/elements/SoLazyElement.h
  database/include/Inventor/elements/SoLightAttenuationElement.h
  database/include/Inventor/elements/SoLightModelElement.h
  database/include/Inventor/elements/SoLinePatternElement.h
  database/include/Inventor/elements/SoLineWidthElement.h
  database/include/Inventor/elements/SoLocalBBoxMatrixElement.h
  database/include/Inventor/elements/SoLongElement.h
  database/include/Inventor/elements/SoMaterialBindingElement.h
  database/include/Inventor/elements/SoModelMatrixElement.h
  database/include/Inventor/elements/SoNormalBindingElement.h
  database/include/Inventor/elements/SoNormalElement.h
  database/include/Inventor/elements/SoOverrideElement.h
  database/include/Inventor/elements/SoPickRayElement.h
  database/include/Inventor/elements/SoPickStyleElement.h
  database/include/Inventor/elements/SoPointSizeElement.h
  database/include/Inventor/elements/SoProfileCoordinateElement.h
  database/include/Inventor/elements/SoProfileElement.h
  database/include/Inventor/elements/SoProjectionMatrixElement.h
  database/include/Inventor/elements/SoReplacedElement.h
  database/include/Inventor/elements/SoShapeHintsElement.h
  database/include/Inventor/elements/SoShapeStyleElement.h
  database/include/Inventor/elements/SoShininessElement.h
  database/include/Inventor/elements/SoSpecularColorElement.h
  database/include/Inventor/elements/SoSubElement.h
  database/include/Inventor/elements/SoSwitchElement.h
  database/include/Inventor/elements/SoTextureBlendColorElement.h
  database/include/Inventor/elements/SoTextureCoordinateBindingElement.h
  database/include/Inventor/elements/SoTextureCoordinateElement.h
  database/include/Inventor/elements/SoTextureImageElement.h
  database/include/Inventor/elements/SoTextureMatrixElement.h
  database/include/Inventor/elements/SoTextureModelElement.h
  database/include/Inventor/elements/SoTextureQualityElement.h
  database/include/Inventor/elements/SoTextureWrapSElement.h
  database/include/Inventor/elements/SoTextureWrapTElement.h
  database/include/Inventor/elements/SoTransparencyElement.h
  database/include/Inventor/elements/SoUnitsElement.h
  database/include/Inventor/elements/SoViewVolumeElement.h
  database/include/Inventor/elements/SoViewingMatrixElement.h
  database/include/Inventor/elements/SoViewportRegionElement.h
  database/include/Inventor/elements/SoWindowElement.h
  database/include/Inventor/engines/SoBoolOperation.h
  database/include/Inventor/engines/SoCalculator.h
  database/include/Inventor/engines/SoCompose.h
  database/include/Inventor/engines/SoComputeBoundingBox.h
  database/include/Inventor/engines/SoConcatenate.h
  database/include/Inventor/engines/SoCounter.h
  database/include/Inventor/engines/SoElapsedTime.h
  database/include/Inventor/engines/SoEngine.h
  database/include/Inventor/engines/SoEngines.h
  database/include/Inventor/engines/SoFieldConverter.h
  database/include/Inventor/engines/SoGate.h
  database/include/Inventor/engines/SoInterpolate.h
  database/include/Inventor/engines/SoOnOff.h
  database/include/Inventor/engines/SoOneShot.h
  database/include/Inventor/engines/SoOutputData.h
  database/include/Inventor/engines/SoSelectOne.h
  database/include/Inventor/engines/SoSubEngine.h
  database/include/Inventor/engines/SoTimeCounter.h
  database/include/Inventor/engines/SoTransformVec3f.h
  database/include/Inventor/engines/SoTriggerAny.h
  database/include/Inventor/errors/SoDebugError.h
  database/include/Inventor/errors/SoError.h
  database/include/Inventor/errors/SoErrors.h
  database/include/Inventor/errors/SoMemoryError.h
  database/include/Inventor/errors/SoReadError.h
  database/include/Inventor/events/SoButtonEvent.h
  database/include/Inventor/events/SoEvent.h
  database/include/Inventor/events/SoEvents.h
  database/include/Inventor/events/SoKeyboardEvent.h
  database/include/Inventor/events/SoLocation2Event.h
  database/include/Inventor/events/SoMotion3Event.h
  database/include/Inventor/events/SoMouseButtonEvent.h
  database/include/Inventor/events/SoSpaceballButtonEvent.h
  database/include/Inventor/events/SoSubEvent.h
  database/include/Inventor/fields/SoField.h
  database/include/Inventor/fields/SoFieldContainer.h
  database/include/Inventor/fields/SoFieldData.h
  database/include/Inventor/fields/SoFields.h
  database/include/Inventor/fields/SoMFBitMask.h
  database/include/Inventor/fields/SoMFBool.h
  database/include/Inventor/fields/SoMFColor.h
  database/include/Inventor/fields/SoMFEngine.h
  database/include/Inventor/fields/SoMFEnum.h
  database/include/Inventor/fields/SoMFFloat.h
  database/include/Inventor/fields/SoMFInt32.h
  database/include/Inventor/fields/SoMFLong.h
  database/include/Inventor/fields/SoMFMatrix.h
  database/include/Inventor/fields/SoMFName.h
  database/include/Inventor/fields/SoMFNode.h
  database/include/Inventor/fields/SoMFPath.h
  database/include/Inventor/fields/SoMFPlane.h
  database/include/Inventor/fields/SoMFRotation.h
  database/include/Inventor/fields/SoMFShort.h
  database/include/Inventor/fields/SoMFString.h
  database/include/Inventor/fields/SoMFTime.h
  database/include/Inventor/fields/SoMFUInt32.h
  database/include/Inventor/fields/SoMFULong.h
  database/include/Inventor/fields/SoMFUShort.h
  database/include/Inventor/fields/SoMFVec2f.h
  database/include/Inventor/fields/SoMFVec3f.h
  database/include/Inventor/fields/SoMFVec4f.h
  database/include/Inventor/fields/SoSFBitMask.h
  database/include/Inventor/fields/SoSFBool.h
  database/include/Inventor/fields/SoSFColor.h
  database/include/Inventor/fields/SoSFEngine.h
  database/include/Inventor/fields/SoSFEnum.h
  database/include/Inventor/fields/SoSFFloat.h
  database/include/Inventor/fields/SoSFImage.h
  database/include/Inventor/fields/SoSFInt32.h
  database/include/Inventor/fields/SoSFLong.h
  database/include/Inventor/fields/SoSFMatrix.h
  database/include/Inventor/fields/SoSFName.h
  database/include/Inventor/fields/SoSFNode.h
  database/include/Inventor/fields/SoSFPath.h
  database/include/Inventor/fields/SoSFPlane.h
  database/include/Inventor/fields/SoSFRotation.h
  database/include/Inventor/fields/SoSFShort.h
  database/include/Inventor/fields/SoSFString.h
  database/include/Inventor/fields/SoSFTime.h
  database/include/Inventor/fields/SoSFTrigger.h
  database/include/Inventor/fields/SoSFUInt32.h
  database/include/Inventor/fields/SoSFULong.h
  database/include/Inventor/fields/SoSFUShort.h
  database/include/Inventor/fields/SoSFVec2f.h
  database/include/Inventor/fields/SoSFVec3f.h
  database/include/Inventor/fields/SoSFVec4f.h
  database/include/Inventor/fields/SoSubField.h
  database/include/Inventor/fields/SoSFInt64.h
  database/include/Inventor/fields/SoMFInt64.h
  database/include/Inventor/misc/SoAuditorList.h
  database/include/Inventor/misc/SoBase.h
  database/include/Inventor/misc/SoBasic.h
  database/include/Inventor/misc/SoByteStream.h
  database/include/Inventor/misc/SoCallbackList.h
  database/include/Inventor/misc/SoChildList.h
  database/include/Inventor/misc/SoCompactPathList.h
  database/include/Inventor/misc/SoNormalGenerator.h
  database/include/Inventor/misc/SoNotification.h
  database/include/Inventor/misc/SoState.h
  database/include/Inventor/misc/SoTempPath.h
  database/include/Inventor/misc/SoTranscribe.h
  database/include/Inventor/misc/upgraders/SoUpgrader.h
  database/include/Inventor/misc/upgraders/SoV1CustomNode.h
  database/include/Inventor/nodes/SoAnnotation.h
  database/include/Inventor/nodes/SoArray.h
  database/include/Inventor/nodes/SoAsciiText.h
  database/include/Inventor/nodes/SoBaseColor.h
  database/include/Inventor/nodes/SoBlinker.h
  database/include/Inventor/nodes/SoCallback.h
  database/include/Inventor/nodes/SoCamera.h
  database/include/Inventor/nodes/SoClipPlane.h
  database/include/Inventor/nodes/SoColorIndex.h
  database/include/Inventor/nodes/SoComplexity.h
  database/include/Inventor/nodes/SoCone.h
  database/include/Inventor/nodes/SoCoordinate3.h
  database/include/Inventor/nodes/SoCoordinate4.h
  database/include/Inventor/nodes/SoCube.h
  database/include/Inventor/nodes/SoCylinder.h
  database/include/Inventor/nodes/SoDirectionalLight.h
  database/include/Inventor/nodes/SoDrawStyle.h
  database/include/Inventor/nodes/SoEnvironment.h
  database/include/Inventor/nodes/SoEventCallback.h
  database/include/Inventor/nodes/SoFaceSet.h
  database/include/Inventor/nodes/SoFile.h
  database/include/Inventor/nodes/SoFont.h
  database/include/Inventor/nodes/SoFontStyle.h
  database/include/Inventor/nodes/SoGroup.h
  database/include/Inventor/nodes/SoIndexedFaceSet.h
  database/include/Inventor/nodes/SoIndexedLineSet.h
  database/include/Inventor/nodes/SoIndexedNurbsCurve.h
  database/include/Inventor/nodes/SoIndexedNurbsSurface.h
  database/include/Inventor/nodes/SoIndexedShape.h
  database/include/Inventor/nodes/SoIndexedTriangleStripSet.h
  database/include/Inventor/nodes/SoInfo.h
  database/include/Inventor/nodes/SoLOD.h
  database/include/Inventor/nodes/SoLabel.h
  database/include/Inventor/nodes/SoLevelOfDetail.h
  database/include/Inventor/nodes/SoLight.h
  database/include/Inventor/nodes/SoLightModel.h
  database/include/Inventor/nodes/SoLineSet.h
  database/include/Inventor/nodes/SoLinearProfile.h
  database/include/Inventor/nodes/SoLocateHighlight.h
  database/include/Inventor/nodes/SoMaterial.h
  database/include/Inventor/nodes/SoMaterialBinding.h
  database/include/Inventor/nodes/SoMaterialIndex.h
  database/include/Inventor/nodes/SoMatrixTransform.h
  database/include/Inventor/nodes/SoMultipleCopy.h
  database/include/Inventor/nodes/SoNode.h
  database/include/Inventor/nodes/SoNodes.h
  database/include/Inventor/nodes/SoNonIndexedShape.h
  database/include/Inventor/nodes/SoNormal.h
  database/include/Inventor/nodes/SoNormalBinding.h
  database/include/Inventor/nodes/SoNurbsCurve.h
  database/include/Inventor/nodes/SoNurbsProfile.h
  database/include/Inventor/nodes/SoNurbsSurface.h
  database/include/Inventor/nodes/SoOrthographicCamera.h
  database/include/Inventor/nodes/SoPackedColor.h
  database/include/Inventor/nodes/SoPathSwitch.h
  database/include/Inventor/nodes/SoPendulum.h
  database/include/Inventor/nodes/SoPerspectiveCamera.h
  database/include/Inventor/nodes/SoPickStyle.h
  database/include/Inventor/nodes/SoPointLight.h
  database/include/Inventor/nodes/SoPointSet.h
  database/include/Inventor/nodes/SoProfile.h
  database/include/Inventor/nodes/SoProfileCoordinate2.h
  database/include/Inventor/nodes/SoProfileCoordinate3.h
  database/include/Inventor/nodes/SoQuadMesh.h
  database/include/Inventor/nodes/SoResetTransform.h
  database/include/Inventor/nodes/SoRotation.h
  database/include/Inventor/nodes/SoRotationXYZ.h
  database/include/Inventor/nodes/SoRotor.h
  database/include/Inventor/nodes/SoScale.h
  database/include/Inventor/nodes/SoSeparator.h
  database/include/Inventor/nodes/SoShape.h
  database/include/Inventor/nodes/SoShapeHints.h
  database/include/Inventor/nodes/SoShuttle.h
  database/include/Inventor/nodes/SoSphere.h
  database/include/Inventor/nodes/SoSpotLight.h
  database/include/Inventor/nodes/SoSubNode.h
  database/include/Inventor/nodes/SoSwitch.h
  database/include/Inventor/nodes/SoText2.h
  database/include/Inventor/nodes/SoText3.h
  database/include/Inventor/nodes/SoTexture2.h
  database/include/Inventor/nodes/SoTexture2Transform.h
  database/include/Inventor/nodes/SoTextureCoordinate2.h
  database/include/Inventor/nodes/SoTextureCoordinateBinding.h
  database/include/Inventor/nodes/SoTextureCoordinateDefault.h
  database/include/Inventor/nodes/SoTextureCoordinateEnvironment.h
  database/include/Inventor/nodes/SoTextureCoordinateFunction.h
  database/include/Inventor/nodes/SoTextureCoordinatePlane.h
  database/include/Inventor/nodes/SoTransform.h
  database/include/Inventor/nodes/SoTransformSeparator.h
  database/include/Inventor/nodes/SoTransformation.h
  database/include/Inventor/nodes/SoTranslation.h
  database/include/Inventor/nodes/SoTriangleStripSet.h
  database/include/Inventor/nodes/SoUnits.h
  database/include/Inventor/nodes/SoVertexArray.h
  database/include/Inventor/nodes/SoVertexProperty.h
  database/include/Inventor/nodes/SoVertexShape.h
  database/include/Inventor/nodes/SoWWWAnchor.h
  database/include/Inventor/nodes/SoWWWInline.h
  database/include/Inventor/nodes/glVertArray.h
  database/include/Inventor/projectors/SbCylinderPlaneProjector.h
  database/include/Inventor/projectors/SbCylinderProjector.h
  database/include/Inventor/projectors/SbCylinderSectionProjector.h
  database/include/Inventor/projectors/SbCylinderSheetProjector.h
  database/include/Inventor/projectors/SbLineProjector.h
  database/include/Inventor/projectors/SbPlaneProjector.h
  database/include/Inventor/projectors/SbProjector.h
  database/include/Inventor/projectors/SbProjectors.h
  database/include/Inventor/projectors/SbSpherePlaneProjector.h
  database/include/Inventor/projectors/SbSphereProjector.h
  database/include/Inventor/projectors/SbSphereSectionProjector.h
  database/include/Inventor/projectors/SbSphereSheetProjector.h
  database/include/Inventor/sensors/SoAlarmSensor.h
  database/include/Inventor/sensors/SoDataSensor.h
  database/include/Inventor/sensors/SoDelayQueueSensor.h
  database/include/Inventor/sensors/SoFieldSensor.h
  database/include/Inventor/sensors/SoIdleSensor.h
  database/include/Inventor/sensors/SoNodeSensor.h
  database/include/Inventor/sensors/SoOneShotSensor.h
  database/include/Inventor/sensors/SoPathSensor.h
  database/include/Inventor/sensors/SoSensor.h
  database/include/Inventor/sensors/SoSensorManager.h
  database/include/Inventor/sensors/SoSensors.h
  database/include/Inventor/sensors/SoTimerQueueSensor.h
  database/include/Inventor/sensors/SoTimerSensor.h
  database/include/SoDebug.h
  database/include/SoUnknownEngine.h
  database/include/SoUnknownNode.h
  database/include/machine.h
  database/src/so/engines/SoCalcExpr.h
  database/src/so/engines/SoEngineUtil.h
  database/src/so/engines/SoFieldConverters.h
  database/src/so/fields/SoGlobalField.h
  database/src/so/nodes/nurbs/SoAddPrefix.h
  database/src/so/nodes/nurbs/SoCurveMaps.h
  database/src/so/nodes/nurbs/SoCurveRender.h
  database/src/so/nodes/nurbs/SoCurveRenderEval.h
  database/src/so/nodes/nurbs/SoGLRender.h
  database/src/so/nodes/nurbs/SoPickEvals.h
  database/src/so/nodes/nurbs/SoPickMaps.h
  database/src/so/nodes/nurbs/SoPickRender.h
  database/src/so/nodes/nurbs/SoPrimEvals.h
  database/src/so/nodes/nurbs/SoPrimMaps.h
  database/src/so/nodes/nurbs/SoPrimRender.h
  database/src/so/nodes/nurbs/_defines.h
  database/src/so/nodes/nurbs/_undefs.h
  database/src/so/nodes/nurbs/clients/gl4base.h
  database/src/so/nodes/nurbs/clients/gl4curveval.h
  database/src/so/nodes/nurbs/clients/gl4surfeval.h
  database/src/so/nodes/nurbs/clients/gl4types.h
  database/src/so/nodes/nurbs/clients/isocurveeval.h
  database/src/so/nodes/nurbs/clients/softcurvemaps.h
  database/src/so/nodes/nurbs/clients/softcurveval.h
  database/src/so/nodes/nurbs/clients/softcurvmap.h
  database/src/so/nodes/nurbs/clients/softrenderer.h
  database/src/so/nodes/nurbs/clients/softsurfacemaps.h
  database/src/so/nodes/nurbs/clients/softsurfeval.h
  database/src/so/nodes/nurbs/clients/softsurfmap.h
  database/src/so/nodes/nurbs/clients/typestringtable.h
  database/src/so/nodes/nurbs/head/arc.h
  database/src/so/nodes/nurbs/head/arcsorter.h
  database/src/so/nodes/nurbs/head/arctess.h
  database/src/so/nodes/nurbs/head/backend.h
  database/src/so/nodes/nurbs/head/basiccrveval.h
  database/src/so/nodes/nurbs/head/basicsurfeval.h
  database/src/so/nodes/nurbs/head/bezierarc.h
  database/src/so/nodes/nurbs/head/bin.h
  database/src/so/nodes/nurbs/head/bufpool.h
  database/src/so/nodes/nurbs/head/cachingeval.h
  database/src/so/nodes/nurbs/head/coveandtiler.h
  database/src/so/nodes/nurbs/head/curve.h
  database/src/so/nodes/nurbs/head/curvelist.h
  database/src/so/nodes/nurbs/head/defines.h
  database/src/so/nodes/nurbs/head/displaylist.h
  database/src/so/nodes/nurbs/head/displaymode.h
  database/src/so/nodes/nurbs/head/flist.h
  database/src/so/nodes/nurbs/head/flistsorter.h
  database/src/so/nodes/nurbs/head/glimports.h
  database/src/so/nodes/nurbs/head/gridline.h
  database/src/so/nodes/nurbs/head/gridtrimvertex.h
  database/src/so/nodes/nurbs/head/gridvertex.h
  database/src/so/nodes/nurbs/head/hull.h
  database/src/so/nodes/nurbs/head/jarcloc.h
  database/src/so/nodes/nurbs/head/jumpbuffer.h
  database/src/so/nodes/nurbs/head/knot.h
  database/src/so/nodes/nurbs/head/knotvector.h
  database/src/so/nodes/nurbs/head/mapdesc.h
  database/src/so/nodes/nurbs/head/maplist.h
  database/src/so/nodes/nurbs/head/mesher.h
  database/src/so/nodes/nurbs/head/myassert.h
  database/src/so/nodes/nurbs/head/myglimports.h
  database/src/so/nodes/nurbs/head/mymath.h
  database/src/so/nodes/nurbs/head/mysetjmp.h
  database/src/so/nodes/nurbs/head/mystdio.h
  database/src/so/nodes/nurbs/head/mystdlib.h
  database/src/so/nodes/nurbs/head/mystring.h
  database/src/so/nodes/nurbs/head/nurbsconsts.h
  database/src/so/nodes/nurbs/head/nurbstess.h
  database/src/so/nodes/nurbs/head/patch.h
  database/src/so/nodes/nurbs/head/patchlist.h
  database/src/so/nodes/nurbs/head/pwlarc.h
  database/src/so/nodes/nurbs/head/quilt.h
  database/src/so/nodes/nurbs/head/reader.h
  database/src/so/nodes/nurbs/head/renderhints.h
  database/src/so/nodes/nurbs/head/simplemath.h
  database/src/so/nodes/nurbs/head/slicer.h
  database/src/so/nodes/nurbs/head/sorter.h
  database/src/so/nodes/nurbs/head/subdivider.h
  database/src/so/nodes/nurbs/head/trimline.h
  database/src/so/nodes/nurbs/head/trimregion.h
  database/src/so/nodes/nurbs/head/trimvertex.h
  database/src/so/nodes/nurbs/head/trimvertpool.h
  database/src/so/nodes/nurbs/head/types.h
  database/src/so/nodes/nurbs/head/uarray.h
  database/src/so/nodes/nurbs/head/varray.h
  database/src/so/nodes/readGIF.h
  database/src/so/upgraders/SoUpgraders.h
  database/src/so/upgraders/SoV1DrawStyle.h
  database/src/so/upgraders/SoV1Environment.h
  database/src/so/upgraders/SoV1IndexedTriangleMesh.h
  database/src/so/upgraders/SoV1LayerGroup.h
  database/src/so/upgraders/SoV1LightModel.h
  database/src/so/upgraders/SoV1Material.h
  database/src/so/upgraders/SoV1PackedColor.h
  database/src/so/upgraders/SoV1PickStyle.h
  database/src/so/upgraders/SoV1Separator.h
  database/src/so/upgraders/SoV1ShapeHints.h
  database/src/so/upgraders/SoV1Text2.h
  database/src/so/upgraders/SoV1Text3.h
  database/src/so/upgraders/SoV1Texture2.h
  database/src/so/upgraders/SoV1TextureCoordinateCube.h
  database/src/so/upgraders/SoV1TextureCoordinateCylinder.h
  database/src/so/upgraders/SoV1TextureCoordinateEnvironment.h
  database/src/so/upgraders/SoV1TextureCoordinatePlane.h
  database/src/so/upgraders/SoV1TextureCoordinateSphere.h
  database/src/so/upgraders/SoV2AsciiText.h
  database/src/so/upgraders/SoV2FontStyle.h
  database/src/so/upgraders/SoV2LOD.h
  database/src/so/upgraders/SoV2MaterialIndex.h
  database/src/so/upgraders/SoV2Text2.h
  database/src/so/upgraders/SoV2Text3.h
  database/src/so/upgraders/SoV2VertexProperty.h
  database/src/so/upgraders/SoV2WWWAnchor.h
  database/src/so/upgraders/SoV2WWWInline.h
  interaction/include/Inventor/SoInteraction.h
  interaction/include/Inventor/SoSceneManager.h
  interaction/include/Inventor/actions/SoBoxHighlightRenderAction.h
  interaction/include/Inventor/actions/SoLineHighlightRenderAction.h
  interaction/include/Inventor/draggers/SoCenterballDragger.h
  interaction/include/Inventor/draggers/SoDirectionalLightDragger.h
  interaction/include/Inventor/draggers/SoDragPointDragger.h
  interaction/include/Inventor/draggers/SoDragger.h
  interaction/include/Inventor/draggers/SoHandleBoxDragger.h
  interaction/include/Inventor/draggers/SoJackDragger.h
  interaction/include/Inventor/draggers/SoPointLightDragger.h
  interaction/include/Inventor/draggers/SoRotateCylindricalDragger.h
  interaction/include/Inventor/draggers/SoRotateDiscDragger.h
  interaction/include/Inventor/draggers/SoRotateSphericalDragger.h
  interaction/include/Inventor/draggers/SoScale1Dragger.h
  interaction/include/Inventor/draggers/SoScale2Dragger.h
  interaction/include/Inventor/draggers/SoScale2UniformDragger.h
  interaction/include/Inventor/draggers/SoScaleUniformDragger.h
  interaction/include/Inventor/draggers/SoSpotLightDragger.h
  interaction/include/Inventor/draggers/SoTabBoxDragger.h
  interaction/include/Inventor/draggers/SoTabPlaneDragger.h
  interaction/include/Inventor/draggers/SoTrackballDragger.h
  interaction/include/Inventor/draggers/SoTransformBoxDragger.h
  interaction/include/Inventor/draggers/SoTransformerDragger.h
  interaction/include/Inventor/draggers/SoTranslate1Dragger.h
  interaction/include/Inventor/draggers/SoTranslate2Dragger.h
  interaction/include/Inventor/manips/SoCenterballManip.h
  interaction/include/Inventor/manips/SoDirectionalLightManip.h
  interaction/include/Inventor/manips/SoHandleBoxManip.h
  interaction/include/Inventor/manips/SoJackManip.h
  interaction/include/Inventor/manips/SoPointLightManip.h
  interaction/include/Inventor/manips/SoSpotLightManip.h
  interaction/include/Inventor/manips/SoTabBoxManip.h
  interaction/include/Inventor/manips/SoTrackballManip.h
  interaction/include/Inventor/manips/SoTransformBoxManip.h
  interaction/include/Inventor/manips/SoTransformManip.h
  interaction/include/Inventor/manips/SoTransformerManip.h
  interaction/include/Inventor/nodekits/SoInteractionKit.h
  interaction/include/Inventor/nodes/SoAntiSquish.h
  interaction/include/Inventor/nodes/SoSelection.h
  interaction/include/Inventor/nodes/SoSurroundScale.h
  interaction/src/draggers/geom/SoCenterballDraggerGeom.h
  interaction/src/draggers/geom/SoDirectionalLightDraggerGeom.h
  interaction/src/draggers/geom/SoDragPointDraggerGeom.h
  interaction/src/draggers/geom/SoHandleBoxDraggerGeom.h
  interaction/src/draggers/geom/SoJackDraggerGeom.h
  interaction/src/draggers/geom/SoPointLightDraggerGeom.h
  interaction/src/draggers/geom/SoRotateCylindricalDraggerGeom.h
  interaction/src/draggers/geom/SoRotateDiscDraggerGeom.h
  interaction/src/draggers/geom/SoRotateSphericalDraggerGeom.h
  interaction/src/draggers/geom/SoScale1DraggerGeom.h
  interaction/src/draggers/geom/SoScale2DraggerGeom.h
  interaction/src/draggers/geom/SoScale2UniformDraggerGeom.h
  interaction/src/draggers/geom/SoScaleUniformDraggerGeom.h
  interaction/src/draggers/geom/SoSpotLightDraggerGeom.h
  interaction/src/draggers/geom/SoTabBoxDraggerGeom.h
  interaction/src/draggers/geom/SoTabPlaneDraggerGeom.h
  interaction/src/draggers/geom/SoTrackballDraggerGeom.h
  interaction/src/draggers/geom/SoTransformBoxDraggerGeom.h
  interaction/src/draggers/geom/SoTransformerDraggerGeom.h
  interaction/src/draggers/geom/SoTranslate1DraggerGeom.h
  interaction/src/draggers/geom/SoTranslate2DraggerGeom.h
  nodekits/include/Inventor/SoNodeKitPath.h
  nodekits/include/Inventor/details/SoNodeKitDetail.h
  nodekits/include/Inventor/misc/upgraders/SoV1AppearanceKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1BaseKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1CameraKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1ConeKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1CubeKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1CylinderKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1DirectionalLightKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1FaceSetKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1GroupKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1IndexedFaceSetKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1IndexedLineSetKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1IndexedNurbsCurveKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1IndexedNurbsSurfaceKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1IndexedTriangleMeshKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1LightKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1LineSetKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1NodeKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1NodekitCatalog.h
  nodekits/include/Inventor/misc/upgraders/SoV1NodekitParts.h
  nodekits/include/Inventor/misc/upgraders/SoV1NurbsCurveKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1NurbsSurfaceKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1OrthographicCameraKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1PerspectiveCameraKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1PointLightKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1PointSetKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1QuadMeshKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1SceneKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1ShapeKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1SphereKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1SpotLightKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1SubKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1Text2Kit.h
  nodekits/include/Inventor/misc/upgraders/SoV1Text3Kit.h
  nodekits/include/Inventor/misc/upgraders/SoV1TriangleStripSetKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1VertexShapeKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1WrapperKit.h
  nodekits/include/Inventor/nodekits/SoAppearanceKit.h
  nodekits/include/Inventor/nodekits/SoBaseKit.h
  nodekits/include/Inventor/nodekits/SoCameraKit.h
  nodekits/include/Inventor/nodekits/SoLightKit.h
  nodekits/include/Inventor/nodekits/SoNodeKit.h
  nodekits/include/Inventor/nodekits/SoNodeKitListPart.h
  nodekits/include/Inventor/nodekits/SoNodekitCatalog.h
  nodekits/include/Inventor/nodekits/SoNodekitParts.h
  nodekits/include/Inventor/nodekits/SoSceneKit.h
  nodekits/include/Inventor/nodekits/SoSeparatorKit.h
  nodekits/include/Inventor/nodekits/SoShapeKit.h
  nodekits/include/Inventor/nodekits/SoSubKit.h
  nodekits/include/Inventor/nodekits/SoWrapperKit.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES ${SOURCES}
  database/src/sb/SbBox.cpp
  database/src/sb/SbColor.cpp
  database/src/sb/SbCylinder.cpp
  database/src/sb/SbDict.cpp
  database/src/sb/SbLine.cpp
  database/src/sb/SbMatrix.cpp
  database/src/sb/SbName.cpp
  database/src/sb/SbPList.cpp
  database/src/sb/SbPlane.cpp
  database/src/sb/SbRotation.cpp
  database/src/sb/SbSphere.cpp
  database/src/sb/SbString.cpp
  database/src/sb/SbTime.cpp
  database/src/sb/SbVec.cpp
  database/src/sb/SbView.cpp
  database/src/sb/SbViewportRegion.cpp
  database/src/sb/projectors/SbCylinderPlaneProjector.cpp
  database/src/sb/projectors/SbCylinderProjector.cpp
  database/src/sb/projectors/SbCylinderSectionProjector.cpp
  database/src/sb/projectors/SbCylinderSheetProjector.cpp
  database/src/sb/projectors/SbLineProjector.cpp
  database/src/sb/projectors/SbPlaneProjector.cpp
  database/src/sb/projectors/SbProjector.cpp
  database/src/sb/projectors/SbSpherePlaneProjector.cpp
  database/src/sb/projectors/SbSphereProjector.cpp
  database/src/sb/projectors/SbSphereSectionProjector.cpp
  database/src/sb/projectors/SbSphereSheetProjector.cpp
  database/src/so/SoAuditorList.cpp
  database/src/so/SoBase.cpp
  database/src/so/SoByteStream.cpp
  database/src/so/SoCBList.cpp
  database/src/so/SoChildList.cpp
  database/src/so/SoCompactPathList.cpp
  database/src/so/SoDB.cpp
  database/src/so/SoDebug.cpp
  database/src/so/SoInput.cpp
  database/src/so/SoLists.cpp
  database/src/so/SoNormalGenerator.cpp
  database/src/so/SoNotification.cpp
  database/src/so/SoOutput.cpp
  database/src/so/SoPath.cpp
  database/src/so/SoPickedPoint.cpp
  database/src/so/SoPrimitiveVertex.cpp
  database/src/so/SoState.cpp
  database/src/so/SoTempPath.cpp
  database/src/so/SoTranscribe.cpp
  database/src/so/SoType.cpp
  database/src/so/actions/SoAction.cpp
  database/src/so/actions/SoActionInit.cpp
  database/src/so/actions/SoCallbackAction.cpp
  database/src/so/actions/SoGLRenderAction.cpp
  database/src/so/actions/SoGetBoundingBoxAction.cpp
  database/src/so/actions/SoGetMatrixAction.cpp
  database/src/so/actions/SoHandleEventAction.cpp
  database/src/so/actions/SoPickAction.cpp
  database/src/so/actions/SoRayPickAction.cpp
  database/src/so/actions/SoSearchAction.cpp
  database/src/so/actions/SoWriteAction.cpp
  database/src/so/bundles/SoMaterialBundle.cpp
  database/src/so/bundles/SoNormalBundle.cpp
  database/src/so/bundles/SoTextureCoordinateBundle.cpp
  database/src/so/caches/SoBoundingBoxCache.cpp
  database/src/so/caches/SoCache.cpp
  database/src/so/caches/SoGLCacheList.cpp
  database/src/so/caches/SoGLRenderCache.cpp
  database/src/so/caches/SoNormalCache.cpp
  database/src/so/details/SoConeDetail.cpp
  database/src/so/details/SoCubeDetail.cpp
  database/src/so/details/SoCylinderDetail.cpp
  database/src/so/details/SoDetail.cpp
  database/src/so/details/SoDetailInit.cpp
  database/src/so/details/SoFaceDetail.cpp
  database/src/so/details/SoLineDetail.cpp
  database/src/so/details/SoPointDetail.cpp
  database/src/so/details/SoTextDetail.cpp
  database/src/so/elements/SoAccumulatedElement.cpp
  database/src/so/elements/SoAmbientColorElement.cpp
  database/src/so/elements/SoBBoxModelMatrixElement.cpp
  database/src/so/elements/SoCacheElement.cpp
  database/src/so/elements/SoClipPlaneElement.cpp
  database/src/so/elements/SoComplexityElement.cpp
  database/src/so/elements/SoComplexityTypeElement.cpp
  database/src/so/elements/SoCoordinateElement.cpp
  database/src/so/elements/SoCreaseAngleElement.cpp
  database/src/so/elements/SoDiffuseColorElement.cpp
  database/src/so/elements/SoDrawStyleElement.cpp
  database/src/so/elements/SoElement.cpp
  database/src/so/elements/SoElementInit.cpp
  database/src/so/elements/SoEmissiveColorElement.cpp
  database/src/so/elements/SoFloatElement.cpp
  database/src/so/elements/SoFocalDistanceElement.cpp
  database/src/so/elements/SoFontNameElement.cpp
  database/src/so/elements/SoFontSizeElement.cpp
  database/src/so/elements/SoGLAmbientColorElement.cpp
  database/src/so/elements/SoGLCacheContextElement.cpp
  database/src/so/elements/SoGLClipPlaneElement.cpp
  database/src/so/elements/SoGLCoordinateElement.cpp
  database/src/so/elements/SoGLDiffuseColorElement.cpp
  database/src/so/elements/SoGLDrawStyleElement.cpp
  database/src/so/elements/SoGLEmissiveColorElement.cpp
  database/src/so/elements/SoGLLazyElement.cpp
  database/src/so/elements/SoGLLightIdElement.cpp
  database/src/so/elements/SoGLLinePatternElement.cpp
  database/src/so/elements/SoGLLineWidthElement.cpp
  database/src/so/elements/SoGLModelMatrixElement.cpp
  database/src/so/elements/SoGLNormalElement.cpp
  database/src/so/elements/SoGLPointSizeElement.cpp
  database/src/so/elements/SoGLProjectionMatrixElement.cpp
  database/src/so/elements/SoGLRenderPassElement.cpp
  database/src/so/elements/SoGLShapeHintsElement.cpp
  database/src/so/elements/SoGLShininessElement.cpp
  database/src/so/elements/SoGLSpecularColorElement.cpp
  database/src/so/elements/SoGLTextureCoordinateElement.cpp
  database/src/so/elements/SoGLTextureEnabledElement.cpp
  database/src/so/elements/SoGLTextureImageElement.cpp
  database/src/so/elements/SoGLTextureMatrixElement.cpp
  database/src/so/elements/SoGLUpdateAreaElement.cpp
  database/src/so/elements/SoGLViewingMatrixElement.cpp
  database/src/so/elements/SoGLViewportRegionElement.cpp
  database/src/so/elements/SoInt32Element.cpp
  database/src/so/elements/SoLazyElement.cpp
  database/src/so/elements/SoLightAttenuationElement.cpp
  database/src/so/elements/SoLinePatternElement.cpp
  database/src/so/elements/SoLineWidthElement.cpp
  database/src/so/elements/SoLocalBBoxMatrixElement.cpp
  database/src/so/elements/SoMaterialBindingElement.cpp
  database/src/so/elements/SoModelMatrixElement.cpp
  database/src/so/elements/SoNormalBindingElement.cpp
  database/src/so/elements/SoNormalElement.cpp
  database/src/so/elements/SoOverrideElement.cpp
  database/src/so/elements/SoPickRayElement.cpp
  database/src/so/elements/SoPickStyleElement.cpp
  database/src/so/elements/SoPointSizeElement.cpp
  database/src/so/elements/SoProfileCoordinateElement.cpp
  database/src/so/elements/SoProfileElement.cpp
  database/src/so/elements/SoProjectionMatrixElement.cpp
  database/src/so/elements/SoReplacedElement.cpp
  database/src/so/elements/SoShapeHintsElement.cpp
  database/src/so/elements/SoShapeStyleElement.cpp
  database/src/so/elements/SoShininessElement.cpp
  database/src/so/elements/SoSpecularColorElement.cpp
  database/src/so/elements/SoSwitchElement.cpp
  database/src/so/elements/SoTextureCoordinateBindingElement.cpp
  database/src/so/elements/SoTextureCoordinateElement.cpp
  database/src/so/elements/SoTextureImageElement.cpp
  database/src/so/elements/SoTextureMatrixElement.cpp
  database/src/so/elements/SoTextureQualityElement.cpp
  database/src/so/elements/SoUnitsElement.cpp
  database/src/so/elements/SoViewVolumeElement.cpp
  database/src/so/elements/SoViewingMatrixElement.cpp
  database/src/so/elements/SoViewportRegionElement.cpp
  database/src/so/elements/SoWindowElement.cpp
  database/src/so/engines/SoBoolOperation.cpp
  database/src/so/engines/SoCalcExpr.cpp
  database/src/so/engines/SoCalculator.cpp
  database/src/so/engines/SoCompose.cpp
  database/src/so/engines/SoComputeBoundingBox.cpp
  database/src/so/engines/SoConcatenate.cpp
  database/src/so/engines/SoCounter.cpp
  database/src/so/engines/SoElapsedTime.cpp
  database/src/so/engines/SoEngine.cpp
  database/src/so/engines/SoEngineInit.cpp
  database/src/so/engines/SoFieldConverter.cpp
  database/src/so/engines/SoFieldConverters.cpp
  database/src/so/engines/SoGate.cpp
  database/src/so/engines/SoInterpolate.cpp
  database/src/so/engines/SoOnOff.cpp
  database/src/so/engines/SoOneShot.cpp
  database/src/so/engines/SoOutputData.cpp
  database/src/so/engines/SoSelectOne.cpp
  database/src/so/engines/SoTimeCounter.cpp
  database/src/so/engines/SoTransformVec3f.cpp
  database/src/so/engines/SoTriggerAny.cpp
  database/src/so/engines/SoUnknownEngine.cpp
  database/src/so/errors/SoDebugError.cpp
  database/src/so/errors/SoError.cpp
  database/src/so/errors/SoErrorInit.cpp
  database/src/so/errors/SoMemoryError.cpp
  database/src/so/errors/SoReadError.cpp
  database/src/so/events/SoButtonEvent.cpp
  database/src/so/events/SoEvent.cpp
  database/src/so/events/SoEventInit.cpp
  database/src/so/events/SoKeyboardEvent.cpp
  database/src/so/events/SoLocation2Event.cpp
  database/src/so/events/SoMotion3Event.cpp
  database/src/so/events/SoMouseButtonEvent.cpp
  database/src/so/events/SoSpaceballButtonEvent.cpp
  database/src/so/fields/SoField.cpp
  database/src/so/fields/SoFieldContainer.cpp
  database/src/so/fields/SoFieldData.cpp
  database/src/so/fields/SoFieldInit.cpp
  database/src/so/fields/SoGlobalField.cpp
  database/src/so/fields/SoMFBitMask.cpp
  database/src/so/fields/SoMFBool.cpp
  database/src/so/fields/SoMFColor.cpp
  database/src/so/fields/SoMFEngine.cpp
  database/src/so/fields/SoMFEnum.cpp
  database/src/so/fields/SoMFFloat.cpp
  database/src/so/fields/SoMFInt32.cpp
  database/src/so/fields/SoMFMatrix.cpp
  database/src/so/fields/SoMFName.cpp
  database/src/so/fields/SoMFNode.cpp
  database/src/so/fields/SoMFPath.cpp
  database/src/so/fields/SoMFPlane.cpp
  database/src/so/fields/SoMFRotation.cpp
  database/src/so/fields/SoMFShort.cpp
  database/src/so/fields/SoMFString.cpp
  database/src/so/fields/SoMFTime.cpp
  database/src/so/fields/SoMFUInt32.cpp
  database/src/so/fields/SoMFUShort.cpp
  database/src/so/fields/SoMFVec2f.cpp
  database/src/so/fields/SoMFVec3f.cpp
  database/src/so/fields/SoMFVec4f.cpp
  database/src/so/fields/SoSFBitMask.cpp
  database/src/so/fields/SoSFBool.cpp
  database/src/so/fields/SoSFColor.cpp
  database/src/so/fields/SoSFEngine.cpp
  database/src/so/fields/SoSFEnum.cpp
  database/src/so/fields/SoSFFloat.cpp
  database/src/so/fields/SoSFImage.cpp
  database/src/so/fields/SoSFInt32.cpp
  database/src/so/fields/SoSFMatrix.cpp
  database/src/so/fields/SoSFName.cpp
  database/src/so/fields/SoSFNode.cpp
  database/src/so/fields/SoSFPath.cpp
  database/src/so/fields/SoSFPlane.cpp
  database/src/so/fields/SoSFRotation.cpp
  database/src/so/fields/SoSFShort.cpp
  database/src/so/fields/SoSFString.cpp
  database/src/so/fields/SoSFTime.cpp
  database/src/so/fields/SoSFTrigger.cpp
  database/src/so/fields/SoSFUInt32.cpp
  database/src/so/fields/SoSFUShort.cpp
  database/src/so/fields/SoSFVec2f.cpp
  database/src/so/fields/SoSFVec3f.cpp
  database/src/so/fields/SoSFVec4f.cpp
  database/src/so/fields/SoSFInt64.cpp
  database/src/so/fields/SoMFInt64.cpp
  database/src/so/nodes/SoAnnotation.cpp
  database/src/so/nodes/SoArray.cpp
  database/src/so/nodes/SoAsciiText.cpp
  database/src/so/nodes/SoBaseColor.cpp
  database/src/so/nodes/SoBlinker.cpp
  database/src/so/nodes/SoCallback.cpp
  database/src/so/nodes/SoCamera.cpp
  database/src/so/nodes/SoClipPlane.cpp
  database/src/so/nodes/SoColorIndex.cpp
  database/src/so/nodes/SoComplexity.cpp
  database/src/so/nodes/SoCoordinate3.cpp
  database/src/so/nodes/SoCoordinate4.cpp
  database/src/so/nodes/SoDirectionalLight.cpp
  database/src/so/nodes/SoDrawStyle.cpp
  database/src/so/nodes/SoEnvironment.cpp
  database/src/so/nodes/SoEventCallback.cpp
  database/src/so/nodes/SoFile.cpp
  database/src/so/nodes/SoFont.cpp
  database/src/so/nodes/SoFontStyle.cpp
  database/src/so/nodes/SoGroup.cpp
  database/src/so/nodes/SoIndexedNurbsCurve.cpp
  database/src/so/nodes/SoIndexedNurbsSurface.cpp
  database/src/so/nodes/SoIndexedShape.cpp
  database/src/so/nodes/SoInfo.cpp
  database/src/so/nodes/SoLOD.cpp
  database/src/so/nodes/SoLabel.cpp
  database/src/so/nodes/SoLevelOfDetail.cpp
  database/src/so/nodes/SoLight.cpp
  database/src/so/nodes/SoLightModel.cpp
  database/src/so/nodes/SoLinearProfile.cpp
  database/src/so/nodes/SoLocateHighlight.cpp
  database/src/so/nodes/SoMaterial.cpp
  database/src/so/nodes/SoMaterialBinding.cpp
  database/src/so/nodes/SoMatrixTransform.cpp
  database/src/so/nodes/SoMultipleCopy.cpp
  database/src/so/nodes/SoNode.cpp
  database/src/so/nodes/SoNodeInit.cpp
  database/src/so/nodes/SoNonIndexedShape.cpp
  database/src/so/nodes/SoNormal.cpp
  database/src/so/nodes/SoNormalBinding.cpp
  database/src/so/nodes/SoNurbsCurve.cpp
  database/src/so/nodes/SoNurbsProfile.cpp
  database/src/so/nodes/SoNurbsSurface.cpp
  database/src/so/nodes/SoOrthographicCamera.cpp
  database/src/so/nodes/SoPackedColor.cpp
  database/src/so/nodes/SoPathSwitch.cpp
  database/src/so/nodes/SoPendulum.cpp
  database/src/so/nodes/SoPerspectiveCamera.cpp
  database/src/so/nodes/SoPickStyle.cpp
  database/src/so/nodes/SoPointLight.cpp
  database/src/so/nodes/SoProfile.cpp
  database/src/so/nodes/SoProfileCoordinate2.cpp
  database/src/so/nodes/SoProfileCoordinate3.cpp
  database/src/so/nodes/SoResetTransform.cpp
  database/src/so/nodes/SoRotation.cpp
  database/src/so/nodes/SoRotationXYZ.cpp
  database/src/so/nodes/SoRotor.cpp
  database/src/so/nodes/SoScale.cpp
  database/src/so/nodes/SoSeparator.cpp
  database/src/so/nodes/SoShape.cpp
  database/src/so/nodes/SoShapeHints.cpp
  database/src/so/nodes/SoShuttle.cpp
  database/src/so/nodes/SoSpotLight.cpp
  database/src/so/nodes/SoSwitch.cpp
  database/src/so/nodes/SoText2.cpp
  database/src/so/nodes/SoText3.cpp
  database/src/so/nodes/SoTexture2.cpp
  database/src/so/nodes/SoTexture2Transform.cpp
  database/src/so/nodes/SoTextureCoordinate2.cpp
  database/src/so/nodes/SoTextureCoordinateBinding.cpp
  database/src/so/nodes/SoTextureCoordinateDefault.cpp
  database/src/so/nodes/SoTextureCoordinateEnvironment.cpp
  database/src/so/nodes/SoTextureCoordinateFunction.cpp
  database/src/so/nodes/SoTextureCoordinatePlane.cpp
  database/src/so/nodes/SoTransform.cpp
  database/src/so/nodes/SoTransformSeparator.cpp
  database/src/so/nodes/SoTransformation.cpp
  database/src/so/nodes/SoTranslation.cpp
  database/src/so/nodes/SoUnits.cpp
  database/src/so/nodes/SoUnknownNode.cpp
  database/src/so/nodes/SoVertexArray.cpp
  database/src/so/nodes/SoVertexProperty.cpp
  database/src/so/nodes/SoVertexShape.cpp
  database/src/so/nodes/SoWWWAnchor.cpp
  database/src/so/nodes/SoWWWInline.cpp
  database/src/so/nodes/nurbs/SoCurveMaps.cpp
  database/src/so/nodes/nurbs/SoCurveRender.cpp
  database/src/so/nodes/nurbs/SoCurveRndEvl.cpp
  database/src/so/nodes/nurbs/SoGLRender.cpp
  database/src/so/nodes/nurbs/SoPickEvals.cpp
  database/src/so/nodes/nurbs/SoPickMaps.cpp
  database/src/so/nodes/nurbs/SoPickRender.cpp
  database/src/so/nodes/nurbs/SoPrimEvals.cpp
  database/src/so/nodes/nurbs/SoPrimMaps.cpp
  database/src/so/nodes/nurbs/SoPrimRender.cpp
  database/src/so/nodes/nurbs/clients/nurbsClient.cpp
  database/src/so/nodes/nurbs/libnurbs/libNurbs.cpp
  database/src/so/sensors/SoAlarmSensor.cpp
  database/src/so/sensors/SoDataSensor.cpp
  database/src/so/sensors/SoDelayQueueSensor.cpp
  database/src/so/sensors/SoFieldSensor.cpp
  database/src/so/sensors/SoIdleSensor.cpp
  database/src/so/sensors/SoNodeSensor.cpp
  database/src/so/sensors/SoOneShotSensor.cpp
  database/src/so/sensors/SoPathSensor.cpp
  database/src/so/sensors/SoSensor.cpp
  database/src/so/sensors/SoSensorMgr.cpp
  database/src/so/sensors/SoTimerQueueSensor.cpp
  database/src/so/sensors/SoTimerSensor.cpp
  database/src/so/upgraders/SoUpgrader.cpp
  database/src/so/upgraders/SoUpgraderInit.cpp
  database/src/so/upgraders/SoV1CustomNode.cpp
  database/src/so/upgraders/SoV1DrawStyle.cpp
  database/src/so/upgraders/SoV1Environment.cpp
  database/src/so/upgraders/SoV1IndexedTriangleMesh.cpp
  database/src/so/upgraders/SoV1LayerGroup.cpp
  database/src/so/upgraders/SoV1LightModel.cpp
  database/src/so/upgraders/SoV1Material.cpp
  database/src/so/upgraders/SoV1PackedColor.cpp
  database/src/so/upgraders/SoV1PickStyle.cpp
  database/src/so/upgraders/SoV1Separator.cpp
  database/src/so/upgraders/SoV1ShapeHints.cpp
  database/src/so/upgraders/SoV1Text2.cpp
  database/src/so/upgraders/SoV1Text3.cpp
  database/src/so/upgraders/SoV1Texture2.cpp
  database/src/so/upgraders/SoV1TextureCoordinateCube.cpp
  database/src/so/upgraders/SoV1TextureCoordinateCylinder.cpp
  database/src/so/upgraders/SoV1TextureCoordinateEnvironment.cpp
  database/src/so/upgraders/SoV1TextureCoordinatePlane.cpp
  database/src/so/upgraders/SoV1TextureCoordinateSphere.cpp
  database/src/so/upgraders/SoV2AsciiText.cpp
  database/src/so/upgraders/SoV2FontStyle.cpp
  database/src/so/upgraders/SoV2LOD.cpp
  database/src/so/upgraders/SoV2MaterialIndex.cpp
  database/src/so/upgraders/SoV2Text2.cpp
  database/src/so/upgraders/SoV2Text3.cpp
  database/src/so/upgraders/SoV2VertexProperty.cpp
  database/src/so/upgraders/SoV2WWWAnchor.cpp
  database/src/so/upgraders/SoV2WWWInline.cpp
  database/src/so/linux.cpp
  interaction/src/SoInteraction.cpp
  interaction/src/SoSceneMgr.cpp
  interaction/src/SoSelection.cpp
  interaction/src/actions/SoBoxHL.cpp
  interaction/src/actions/SoLineHL.cpp
  interaction/src/draggers/SoCenterballDragger.cpp
  interaction/src/draggers/SoDirectionalLightDragger.cpp
  interaction/src/draggers/SoDragPointDragger.cpp
  interaction/src/draggers/SoDragger.cpp
  interaction/src/draggers/SoDraggerInit.cpp
  interaction/src/draggers/SoHandleBoxDragger.cpp
  interaction/src/draggers/SoJackDragger.cpp
  interaction/src/draggers/SoPointLightDragger.cpp
  interaction/src/draggers/SoRotateCylindricalDragger.cpp
  interaction/src/draggers/SoRotateDiscDragger.cpp
  interaction/src/draggers/SoRotateSphericalDragger.cpp
  interaction/src/draggers/SoScale1Dragger.cpp
  interaction/src/draggers/SoScale2Dragger.cpp
  interaction/src/draggers/SoScale2UniformDragger.cpp
  interaction/src/draggers/SoScaleUniformDragger.cpp
  interaction/src/draggers/SoSpotLightDragger.cpp
  interaction/src/draggers/SoTabBoxDragger.cpp
  interaction/src/draggers/SoTabPlaneDragger.cpp
  interaction/src/draggers/SoTrackballDragger.cpp
  interaction/src/draggers/SoTransformBoxDragger.cpp
  interaction/src/draggers/SoTransformerDragger.cpp
  interaction/src/draggers/SoTranslate1Dragger.cpp
  interaction/src/draggers/SoTranslate2Dragger.cpp
  interaction/src/manips/SoCenterballManip.cpp
  interaction/src/manips/SoDirLtManip.cpp
  interaction/src/manips/SoHbox.cpp
  interaction/src/manips/SoJackManip.cpp
  interaction/src/manips/SoPtLtManip.cpp
  interaction/src/manips/SoSpotLtManip.cpp
  interaction/src/manips/SoTabBoxManip.cpp
  interaction/src/manips/SoTball.cpp
  interaction/src/manips/SoTransformManip.cpp
  interaction/src/manips/SoTransformerManip.cpp
  interaction/src/manips/SoXformBox.cpp
  interaction/src/nodekits/SoInteractionKit.cpp
  interaction/src/nodes/SoAntiSquish.cpp
  interaction/src/nodes/SoSurroundScale.cpp
  nodekits/src/SoNodeKitPath.cpp
  nodekits/src/details/SoNodeKitDetail.cpp
  nodekits/src/nodekits/SoAppearKit.cpp
  nodekits/src/nodekits/SoBaseKit.cpp
  nodekits/src/nodekits/SoCameraKit.cpp
  nodekits/src/nodekits/SoLightKit.cpp
  nodekits/src/nodekits/SoNkCatalog.cpp
  nodekits/src/nodekits/SoNkParts.cpp
  nodekits/src/nodekits/SoNodeKit.cpp
  nodekits/src/nodekits/SoNodeKitListPart.cpp
  nodekits/src/nodekits/SoSceneKit.cpp
  nodekits/src/nodekits/SoSeparatorKit.cpp
  nodekits/src/nodekits/SoShapeKit.cpp
  nodekits/src/nodekits/SoWrapperKit.cpp
  nodekits/src/upgraders/SoV1AppearKit.cpp
  nodekits/src/upgraders/SoV1BaseKit.cpp
  nodekits/src/upgraders/SoV1CameraKit.cpp
  nodekits/src/upgraders/SoV1ConeKit.cpp
  nodekits/src/upgraders/SoV1CubeKit.cpp
  nodekits/src/upgraders/SoV1CylinderKit.cpp
  nodekits/src/upgraders/SoV1DirLtKit.cpp
  nodekits/src/upgraders/SoV1FaceSetKit.cpp
  nodekits/src/upgraders/SoV1GroupKit.cpp
  nodekits/src/upgraders/SoV1IFaceSetKit.cpp
  nodekits/src/upgraders/SoV1ILineSetKit.cpp
  nodekits/src/upgraders/SoV1INrbCurvKit.cpp
  nodekits/src/upgraders/SoV1INrbSurfKit.cpp
  nodekits/src/upgraders/SoV1ITMshSetKit.cpp
  nodekits/src/upgraders/SoV1LightKit.cpp
  nodekits/src/upgraders/SoV1LineSetKit.cpp
  nodekits/src/upgraders/SoV1NkCatalog.cpp
  nodekits/src/upgraders/SoV1NkParts.cpp
  nodekits/src/upgraders/SoV1NodeKit.cpp
  nodekits/src/upgraders/SoV1NurbCurvKit.cpp
  nodekits/src/upgraders/SoV1NurbSurfKit.cpp
  nodekits/src/upgraders/SoV1OrthoCamKit.cpp
  nodekits/src/upgraders/SoV1PerspCamKit.cpp
  nodekits/src/upgraders/SoV1PointLtKit.cpp
  nodekits/src/upgraders/SoV1PointSetKit.cpp
  nodekits/src/upgraders/SoV1QuadMeshKit.cpp
  nodekits/src/upgraders/SoV1SceneKit.cpp
  nodekits/src/upgraders/SoV1ShapeKit.cpp
  nodekits/src/upgraders/SoV1SphereKit.cpp
  nodekits/src/upgraders/SoV1SpotLtKit.cpp
  nodekits/src/upgraders/SoV1Text2Kit.cpp
  nodekits/src/upgraders/SoV1Text3Kit.cpp
  nodekits/src/upgraders/SoV1TriStripKit.cpp
  nodekits/src/upgraders/SoV1VtxShapeKit.cpp
  nodekits/src/upgraders/SoV1WrapperKit.cpp)

#--------------------------------------------------------------------
# Define the PPP generated sources
#
set(SOURCES ${SOURCES}
  database/src/so/nodes/SoCone.cpp
  database/src/so/nodes/SoCube.cpp
  database/src/so/nodes/SoCylinder.cpp
  database/src/so/nodes/SoFaceSet.cpp
  database/src/so/nodes/SoIndexedFaceSet.cpp
  database/src/so/nodes/SoIndexedLineSet.cpp
  database/src/so/nodes/SoIndexedTriangleStripSet.cpp
  database/src/so/nodes/SoLineSet.cpp
  database/src/so/nodes/SoPointSet.cpp
  database/src/so/nodes/SoQuadMesh.cpp
  database/src/so/nodes/SoSphere.cpp
  database/src/so/nodes/SoTriangleStripSet.cpp)

# image loaders
set(SOURCES ${SOURCES}
  database/src/so/nodes/readGIF.c)
	
set(SOURCES ${SOURCES}
  xip/src/so/events/SoMouseWheelEvent.cpp
  xip/src/SoXip.cpp)
	
# FIXME: Which yacc files should we consider?
#SET(YACCSOURCES
#  database/src/so/engines/SoCalcParse.y)
#SET(SOURCES ${SOURCES}
#  database/src/so/engines/SoCalcParse.tab.c)
set(HEADERS ${HEADERS}
  database/src/so/engines/SoCalcParse_yacc.h)
set(SOURCES ${SOURCES}
  database/src/so/engines/SoCalcParse_yacc.cpp)

if(UNIX AND NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(HEADERS ${HEADERS}
    database/include/Inventor/SoOffscreenRenderer.h)

  set(SOURCES ${SOURCES}
    database/src/so/SoOffscreenRenderer.cpp)
endif(UNIX AND NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if(WIN32)
  set(SOURCES ${SOURCES} initDll.cpp)
endif(WIN32)

#--------------------------------------------------------------------
# Define the object files
#
#set(OBJECTS
#  initDll.obj
#  database/src/sb/Sb.obj
#  database/src/sb/projectors/SbProjectors.obj
#  database/src/so/linux.obj
#  database/src/so/So.obj
#  database/src/so/SoState.obj
#  database/src/so/actions/SoActions.obj
#  database/src/so/bundles/SoBundles.obj
#  database/src/so/caches/SoCaches.obj
#  database/src/so/details/SoDetails.obj
#  database/src/so/elements/SoElement.obj
#  database/src/so/elements/SoElements.obj
#  database/src/so/engines/SoConcatenate.obj
#  database/src/so/engines/SoEngineInit.obj
#  database/src/so/engines/SoEngines.obj
#  database/src/so/engines/SoFieldConverters.obj
#  database/src/so/engines/SoGate.obj 
#  database/src/so/engines/SoSelectOne.obj 
#  database/src/so/errors/SoErrorInit.obj 
#  database/src/so/errors/SoErrors.obj 
#  database/src/so/events/SoEventInit.obj 
#  database/src/so/events/SoEvents.obj 
#  database/src/so/fields/SoField.obj 
#  database/src/so/fields/SoFieldContainer.obj 
#  database/src/so/fields/SoFieldData.obj 
#  database/src/so/fields/SoFieldInit.obj
#  database/src/so/fields/SoFields.obj 
#  database/src/so/fields/SoGlobalField.obj 
#  database/src/so/nodes/readGIF.obj 
#  database/src/so/nodes/SoAnnotation.obj 
#  database/src/so/nodes/SoArray.obj 
#  database/src/so/nodes/SoAsciiText.obj 
#  database/src/so/nodes/SoBaseColor.obj
#  database/src/so/nodes/SoBlinker.obj
#  database/src/so/nodes/SoCallback.obj
#  database/src/so/nodes/SoCamera.obj 
#  database/src/so/nodes/SoClipPlane.obj 
#  database/src/so/nodes/SoColorIndex.obj 
#  database/src/so/nodes/SoComplexity.obj 
#  database/src/so/nodes/SoCone.obj 
#  database/src/so/nodes/SoCoordinate3.obj 
#  database/src/so/nodes/SoCoordinate4.obj
#  database/src/so/nodes/SoCube.obj 
#  database/src/so/nodes/SoCylinder.obj 
#  database/src/so/nodes/SoDirectionalLight.obj 
#  database/src/so/nodes/SoDrawStyle.obj 
#  database/src/so/nodes/SoEnvironment.obj 
#  database/src/so/nodes/SoEventCallback.obj 
#  database/src/so/nodes/SoFaceSet.obj 
#  database/src/so/nodes/SoFile.obj 
#  database/src/so/nodes/SoFont.obj
#  database/src/so/nodes/SoFontStyle.obj 
#  database/src/so/nodes/SoGroup.obj 
#  database/src/so/nodes/SoIndexedFaceSet.obj 
#  database/src/so/nodes/SoIndexedLineSet.obj
#  database/src/so/nodes/SoIndexedNurbsCurve.obj 
#  database/src/so/nodes/SoIndexedNurbsSurface.obj 
#  database/src/so/nodes/SoIndexedShape.obj 
#  database/src/so/nodes/SoIndexedTriangleStripSet.obj 
#  database/src/so/nodes/SoInfo.obj 
#  database/src/so/nodes/SoLabel.obj
#  database/src/so/nodes/SoLevelOfDetail.obj
#  database/src/so/nodes/SoLight.obj 
#  database/src/so/nodes/SoLightModel.obj 
#  database/src/so/nodes/SoLinearProfile.obj 
#  database/src/so/nodes/SoLineSet.obj 
#  database/src/so/nodes/SoLocateHighlight.obj 
#  database/src/so/nodes/SoLOD.obj 
#  database/src/so/nodes/SoMaterial.obj 
#  database/src/so/nodes/SoMaterialBinding.obj 
#  database/src/so/nodes/SoMatrixTransform.obj
#  database/src/so/nodes/SoMultipleCopy.obj 
#  database/src/so/nodes/SoNode.obj 
#  database/src/so/nodes/SoNodeInit.obj 
#  database/src/so/nodes/SoNonIndexedShape.obj 
#  database/src/so/nodes/SoNormal.obj 
#  database/src/so/nodes/SoNormalBinding.obj 
#  database/src/so/nodes/SoNurbsCurve.obj 
#  database/src/so/nodes/SoNurbsProfile.obj 
#  database/src/so/nodes/SoNurbsSurface.obj 
#  database/src/so/nodes/SoOrthographicCamera.obj 
#  database/src/so/nodes/SoPackedColor.obj 
#  database/src/so/nodes/SoPathSwitch.obj 
#  database/src/so/nodes/SoPendulum.obj 
#  database/src/so/nodes/SoPerspectiveCamera.obj 
#  database/src/so/nodes/SoPickStyle.obj 
#  database/src/so/nodes/SoPointLight.obj 
#  database/src/so/nodes/SoPointSet.obj 
#  database/src/so/nodes/SoProfile.obj 
#  database/src/so/nodes/SoProfileCoordinate2.obj 
#  database/src/so/nodes/SoProfileCoordinate3.obj 
#  database/src/so/nodes/SoQuadMesh.obj 
#  database/src/so/nodes/SoResetTransform.obj 
#  database/src/so/nodes/SoRotation.obj 
#  database/src/so/nodes/SoRotationXYZ.obj 
#  database/src/so/nodes/SoRotor.obj 
#  database/src/so/nodes/SoScale.obj
#  database/src/so/nodes/SoSeparator.obj 
#  database/src/so/nodes/SoShape.obj 
#  database/src/so/nodes/SoShapeHints.obj 
#  database/src/so/nodes/SoShuttle.obj 
#  database/src/so/nodes/SoSphere.obj 
#  database/src/so/nodes/SoSpotLight.obj 
#  database/src/so/nodes/SoSwitch.obj 
#  database/src/so/nodes/SoText2.obj 
#  database/src/so/nodes/SoText3.obj 
#  database/src/so/nodes/SoTexture2.obj 
#  database/src/so/nodes/SoTexture2Transform.obj 
#  database/src/so/nodes/SoTextureCoordinate2.obj 
#  database/src/so/nodes/SoTextureCoordinateBinding.obj 
#  database/src/so/nodes/SoTextureCoordinateDefault.obj 
#  database/src/so/nodes/SoTextureCoordinateEnvironment.obj 
#  database/src/so/nodes/SoTextureCoordinateFunction.obj 
#  database/src/so/nodes/SoTextureCoordinatePlane.obj
#  database/src/so/nodes/SoTransform.obj 
#  database/src/so/nodes/SoTransformation.obj 
#  database/src/so/nodes/SoTransformSeparator.obj 
#  database/src/so/nodes/SoTranslation.obj 
#  database/src/so/nodes/SoTriangleStripSet.obj 
#  database/src/so/nodes/SoUnits.obj 
#  database/src/so/nodes/SoUnknownNode.obj 
#  database/src/so/nodes/SoVertexProperty.obj 
#  database/src/so/nodes/SoVertexShape.obj 
#  database/src/so/nodes/SoWWWAnchor.obj 
#  database/src/so/nodes/SoWWWInline.obj 
#  database/src/so/nodes/nurbs/SoNurbs.obj 
#  database/src/so/nodes/nurbs/clients/nurbsClient.obj 
#  database/src/so/nodes/nurbs/libnurbs/libNurbs.obj 
#  database/src/so/sensors/SoSensors.obj 
#  database/src/so/upgraders/SoUpgrader.obj 
#  database/src/so/upgraders/SoUpgraderInit.obj 
#  database/src/so/upgraders/SoUpgraders.obj 
#  interaction/src/SoInteraction.obj 
#  interaction/src/SoSceneMgr.obj 
#  interaction/src/SoSelection.obj 
#  interaction/src/actions/SoBoxHL.obj 
#  interaction/src/actions/SoLineHL.obj 
#  interaction/src/draggers/SoCenterballDragger.obj 
#  interaction/src/draggers/SoDirectionalLightDragger.obj 
#  interaction/src/draggers/SoDragger.obj 
#  interaction/src/draggers/SoDraggerInit.obj 
#  interaction/src/draggers/SoDragPointDragger.obj 
#  interaction/src/draggers/SoHandleBoxDragger.obj 
#  interaction/src/draggers/SoJackDragger.obj 
#  interaction/src/draggers/SoPointLightDragger.obj 
#  interaction/src/draggers/SoRotateCylindricalDragger.obj 
#  interaction/src/draggers/SoRotateDiscDragger.obj 
#  interaction/src/draggers/SoRotateSphericalDragger.obj
#  interaction/src/draggers/SoScale1Dragger.obj 
#  interaction/src/draggers/SoScale2Dragger.obj
#  interaction/src/draggers/SoScale2UniformDragger.obj 
#  interaction/src/draggers/SoScaleUniformDragger.obj 
#  interaction/src/draggers/SoSpotLightDragger.obj 
#  interaction/src/draggers/SoTabBoxDragger.obj 
#  interaction/src/draggers/SoTabPlaneDragger.obj
#  interaction/src/draggers/SoTrackballDragger.obj
#  interaction/src/draggers/SoTransformBoxDragger.obj 
#  interaction/src/draggers/SoTransformerDragger.obj 
#  interaction/src/draggers/SoTranslate1Dragger.obj 
#  interaction/src/draggers/SoTranslate2Dragger.obj
#  interaction/src/manips/SoManips.obj 
#  interaction/src/nodekits/SoInteractionKit.obj 
#  interaction/src/nodes/SoAntiSquish.obj 
#  interaction/src/nodes/SoSurroundScale.obj 
#  mevis/src/SoCatch.obj 
#  mevis/src/SoMeVis.obj
#  mevis/src/SoTrace.obj 
#  mevis/src/utf8_filesupport_win32.obj 
#  mevis/src/elements/SoGLPolygonOffsetElement.obj 
#  mevis/src/elements/SoGLStencilBitsElement.obj 
#  mevis/src/elements/SoPolygonOffsetElement.obj
#  mevis/src/elements/SoStencilBitsElement.obj 
#  mevis/src/fields/SoSFVec2s.obj 
#  mevis/src/fields/SoSFVec3s.obj
#  mevis/src/nodes/SoPolygonOffset.obj 
#  nodekits/src/SoNodeKitPath.obj 
#  nodekits/src/details/SoNodeKitDetail.obj 
#  nodekits/src/nodekits/SoNodeKits.obj 
#  nodekits/src/upgraders/SoNodeKitUpgraders.obj 
#  FL/ang/fl.obj 
#  FL/ang/flclient.obj 
#  FL/ang/flfreetype.obj 
#  image/close.obj 
#  image/filbuf.obj 
#  image/flsbuf.obj 
#  image/name.obj 
#  image/open.obj
#  image/pix.obj
#  image/rdwr.obj 
#  image/rle.obj 
#  image/row.obj
#  xip/src/so/events/SoMouseWheelEvent.obj 
#  xip/src/SoXip.obj)

#foreach(target ${OBJECTS})
#  message("${EXECUTABLE_OUTPUT_PATH}/ppp.exe"
#  ${xipinv_SOURCE_DIR}/database/src/so/engines/SoCalcParse.cpp ${target})
#  @!IF NOT EXIST $(OUTDIR)\. mkdir $(OUTDIR)
#  $(link) $(LDFLAGS) /OUT:"$(TARGET)" $(OBJECTS) $(LIBS)
#	mt.exe -manifest $(TARGET).manifest -outputresource:$(TARGET);2
#endforeach(target ${OBJECTS})

#tools/ppp/ppp.exe:
#  @cl /Fe"tools/ppp/ppp.exe" /I "lib/mevis/include" /I
# "lib/database/include" /I "lib/xip/include" # /D_INVENTOR_ /DWIN32
# /DINVENTOR_API= /D__SGIOIV_BUILD_DLL /TP tools/ppp/ppp.cpp


#--------------------------------------------------------------------
# Compile the library
#
add_library(xipinv240 SHARED ${SOURCES} ${HEADERS})

if(UNIX)
  set_target_properties(xipinv240
    PROPERTIES VERSION 2.40 SOVERSION 2.40)
endif(UNIX)


#--------------------------------------------------------------------
# Link the library
#
target_link_libraries(xipinv240
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${JPEG_LIBRARIES}
  ${FREETYPE_LIBRARIES}
  FL
  image
  ${ICONV_LIBRARY})

if(WIN32)
  target_link_libraries(xipinv240
    jpeg freetype2 Ws2_32)
endif(WIN32)

#--------------------------------------------------------------------
# Install the library
#
install(TARGETS xipinv240
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug)

install(TARGETS xipinv240
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release)


if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipinv240d.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)

