IVDEPTH = ..
include $(IVDEPTH)/make/ivcommondefs

ifeq ($(usingWin32), 1)
ifneq (, $(findstring debug, $(LIBTYPE)))
LIBDSO = Inventor_d.dll
else
LIBDSO = Inventor.dll
endif
else
LIBDSO = libInventor.so
endif

LLDDSOOPTS += -L$(IVDEPTH)/libimage -L$(FLDIR)

ifeq ($(usingWin32), 1)
LLDLIBS = \
	-llibjpeg -llibimage $(FLLIB) \
        -lglu32 -lopengl32 \
        -lwsock32
else
LLDLIBS = \
	-ljpeg -limage $(FLLIB) \
        -lX11 -lm \
        -lGLU -lGL
endif

OBJECTS = \
	./database/src/sb/projectors/SbProjectors.obj \
	./database/src/sb/Sb.obj \
	./database/src/so/actions/SoActions.obj \
	./database/src/so/bundles/SoBundles.obj \
	./database/src/so/caches/SoCaches.obj \
	./database/src/so/details/SoDetails.obj \
	./database/src/so/elements/SoElement.obj \
	./database/src/so/elements/SoElements.obj \
	./database/src/so/engines/SoEngines.obj \
	./database/src/so/engines/SoConcatenate.obj \
	./database/src/so/engines/SoEngineInit.obj \
	./database/src/so/engines/SoFieldConverters.obj \
	./database/src/so/engines/SoGate.obj \
	./database/src/so/engines/SoSelectOne.obj \
	./database/src/so/errors/SoErrors.obj \
	./database/src/so/errors/SoErrorInit.obj \
	./database/src/so/events/SoEventInit.obj \
	./database/src/so/events/SoEvents.obj \
	./database/src/so/fields/SoField.obj \
	./database/src/so/fields/SoFieldContainer.obj \
	./database/src/so/fields/SoFieldData.obj \
	./database/src/so/fields/SoFieldInit.obj \
	./database/src/so/fields/SoFields.obj \
	./database/src/so/fields/SoGlobalField.obj \
	./database/src/so/nodes/nurbs/clients/nurbsClient.obj \
	./database/src/so/nodes/nurbs/libnurbs/libNurbs.obj \
	./database/src/so/nodes/nurbs/SoNurbs.obj \
	./database/src/so/nodes/SoNode.obj \
	./database/src/so/nodes/SoNodeInit.obj \
	./database/src/so/nodes/SoAnnotation.obj \
	./database/src/so/nodes/SoArray.obj \
	./database/src/so/nodes/SoAsciiText.obj \
	./database/src/so/nodes/SoBaseColor.obj \
	./database/src/so/nodes/SoBlinker.obj \
	./database/src/so/nodes/SoCallback.obj \
	./database/src/so/nodes/SoCamera.obj \
	./database/src/so/nodes/SoClipPlane.obj \
	./database/src/so/nodes/SoColorIndex.obj \
	./database/src/so/nodes/SoComplexity.obj \
	./database/src/so/nodes/SoCone.obj \
	./database/src/so/nodes/SoCoordinate3.obj \
	./database/src/so/nodes/SoCube.obj \
	./database/src/so/nodes/SoCylinder.obj \
	./database/src/so/nodes/SoCoordinate4.obj \
	./database/src/so/nodes/SoDrawStyle.obj \
	./database/src/so/nodes/SoDirectionalLight.obj \
	./database/src/so/nodes/SoEnvironment.obj \
	./database/src/so/nodes/SoFaceSet.obj \
	./database/src/so/nodes/SoFile.obj \
	./database/src/so/nodes/SoFont.obj \
	./database/src/so/nodes/SoGroup.obj \
	./database/src/so/nodes/SoEventCallback.obj \
	./database/src/so/nodes/SoFontStyle.obj \
	./database/src/so/nodes/SoIndexedFaceSet.obj \
	./database/src/so/nodes/SoIndexedLineSet.obj \
	./database/src/so/nodes/SoInfo.obj \
	./database/src/so/nodes/SoIndexedNurbsCurve.obj \
	./database/src/so/nodes/SoIndexedShape.obj \
	./database/src/so/nodes/SoLOD.obj \
	./database/src/so/nodes/SoLabel.obj \
	./database/src/so/nodes/SoLight.obj \
	./database/src/so/nodes/SoIndexedNurbsSurface.obj \
	./database/src/so/nodes/SoLineSet.obj \
	./database/src/so/nodes/SoLevelOfDetail.obj \
	./database/src/so/nodes/SoMaterial.obj \
	./database/src/so/nodes/SoLocateHighlight.obj \
	./database/src/so/nodes/SoLightModel.obj \
	./database/src/so/nodes/SoLinearProfile.obj \
	./database/src/so/nodes/SoNormal.obj \
	./database/src/so/nodes/SoMaterialBinding.obj \
	./database/src/so/nodes/SoMultipleCopy.obj \
	./database/src/so/nodes/SoNurbsCurve.obj \
	./database/src/so/nodes/SoNurbsProfile.obj \
	./database/src/so/nodes/SoMatrixTransform.obj \
	./database/src/so/nodes/SoNurbsSurface.obj \
	./database/src/so/nodes/SoPackedColor.obj \
	./database/src/so/nodes/SoPendulum.obj \
	./database/src/so/nodes/SoNonIndexedShape.obj \
	./database/src/so/nodes/SoPathSwitch.obj \
	./database/src/so/nodes/SoPointSet.obj \
	./database/src/so/nodes/SoProfile.obj \
	./database/src/so/nodes/SoNormalBinding.obj \
	./database/src/so/nodes/SoIndexedTriangleStripSet.obj \
	./database/src/so/nodes/SoQuadMesh.obj \
	./database/src/so/nodes/SoRotation.obj \
	./database/src/so/nodes/SoPickStyle.obj \
	./database/src/so/nodes/SoRotor.obj \
	./database/src/so/nodes/SoPointLight.obj \
	./database/src/so/nodes/SoScale.obj \
	./database/src/so/nodes/SoShape.obj \
	./database/src/so/nodes/SoShuttle.obj \
	./database/src/so/nodes/SoOrthographicCamera.obj \
	./database/src/so/nodes/SoRotationXYZ.obj \
	./database/src/so/nodes/SoSphere.obj \
	./database/src/so/nodes/SoSwitch.obj \
	./database/src/so/nodes/SoText2.obj \
	./database/src/so/nodes/SoPerspectiveCamera.obj \
	./database/src/so/nodes/SoProfileCoordinate2.obj \
	./database/src/so/nodes/SoProfileCoordinate3.obj \
	./database/src/so/nodes/SoResetTransform.obj \
	./database/src/so/nodes/SoSeparator.obj \
	./database/src/so/nodes/SoShapeHints.obj \
	./database/src/so/nodes/SoText3.obj \
	./database/src/so/nodes/SoSpotLight.obj \
	./database/src/so/nodes/SoTexture2.obj \
	./database/src/so/nodes/SoTextureCoordinate2.obj \
	./database/src/so/nodes/SoTransform.obj \
	./database/src/so/nodes/SoTextureCoordinateBinding.obj \
	./database/src/so/nodes/SoUnits.obj \
	./database/src/so/nodes/SoTransformation.obj \
	./database/src/so/nodes/readGIF.obj \
	./database/src/so/nodes/SoTranslation.obj \
	./database/src/so/nodes/SoTriangleStripSet.obj \
	./database/src/so/nodes/SoUnknownNode.obj \
	./database/src/so/nodes/SoVertexShape.obj \
	./database/src/so/nodes/SoWWWAnchor.obj \
	./database/src/so/nodes/SoTextureCoordinateDefault.obj \
	./database/src/so/nodes/SoVertexProperty.obj \
	./database/src/so/nodes/SoTextureCoordinateFunction.obj \
	./database/src/so/nodes/SoTextureCoordinateEnvironment.obj \
	./database/src/so/nodes/SoTextureCoordinatePlane.obj \
	./database/src/so/nodes/SoTexture2Transform.obj \
	./database/src/so/nodes/SoTransformSeparator.obj \
	./database/src/so/nodes/SoWWWInline.obj \
	./database/src/so/sensors/SoSensors.obj \
	./database/src/so/upgraders/SoUpgraderInit.obj \
	./database/src/so/upgraders/SoUpgrader.obj \
	./database/src/so/upgraders/SoUpgraders.obj \
	./database/src/so/So.obj \
	./database/src/so/SoState.obj \
	./database/src/so/linux.obj \
	./interaction/src/actions/SoBoxHL.obj \
	./interaction/src/actions/SoLineHL.obj \
	./interaction/src/draggers/SoDraggerInit.obj \
	./interaction/src/draggers/SoCenterballDragger.obj \
	./interaction/src/draggers/SoDirectionalLightDragger.obj \
	./interaction/src/draggers/SoDragPointDragger.obj \
	./interaction/src/draggers/SoDragger.obj \
	./interaction/src/draggers/SoHandleBoxDragger.obj \
	./interaction/src/draggers/SoJackDragger.obj \
	./interaction/src/draggers/SoPointLightDragger.obj \
	./interaction/src/draggers/SoRotateCylindricalDragger.obj \
	./interaction/src/draggers/SoRotateDiscDragger.obj \
	./interaction/src/draggers/SoRotateSphericalDragger.obj \
	./interaction/src/draggers/SoScale1Dragger.obj \
	./interaction/src/draggers/SoScale2Dragger.obj \
	./interaction/src/draggers/SoScale2UniformDragger.obj \
	./interaction/src/draggers/SoScaleUniformDragger.obj \
	./interaction/src/draggers/SoSpotLightDragger.obj \
	./interaction/src/draggers/SoTabBoxDragger.obj \
	./interaction/src/draggers/SoTabPlaneDragger.obj \
	./interaction/src/draggers/SoTrackballDragger.obj \
	./interaction/src/draggers/SoTransformBoxDragger.obj \
	./interaction/src/draggers/SoTransformerDragger.obj \
	./interaction/src/draggers/SoTranslate1Dragger.obj \
	./interaction/src/draggers/SoTranslate2Dragger.obj \
	./interaction/src/manips/SoManips.obj \
	./interaction/src/nodekits/SoInteractionKit.obj \
	./interaction/src/nodes/SoAntiSquish.obj \
	./interaction/src/nodes/SoSurroundScale.obj \
	./interaction/src/SoInteraction.obj \
	./interaction/src/SoSceneMgr.obj \
	./interaction/src/SoSelection.obj \
	./nodekits/src/details/SoNodeKitDetail.obj \
	./nodekits/src/nodekits/SoNodeKits.obj \
	./nodekits/src/upgraders/SoNodeKitUpgraders.obj \
	./nodekits/src/SoNodeKitPath.obj \
	./mevis/src/SoMeVis.obj \
	./mevis/src/SoCatch.obj \
	./mevis/src/SoTrace.obj \
	./mevis/src/elements/SoGLPolygonOffsetElement.obj \
	./mevis/src/elements/SoGLStencilBitsElement.obj \
	./mevis/src/elements/SoPolygonOffsetElement.obj \
	./mevis/src/elements/SoStencilBitsElement.obj \
	./mevis/src/fields/SoSFVec2s.obj \
	./mevis/src/fields/SoSFVec3s.obj \
	./mevis/src/nodes/SoPolygonOffset.obj

ifeq ($(usingWin32), 1)
OBJECTS += \
	./mevis/src/utf8_filesupport_win32.obj

DSOOBJECTS = \
	./initDll.obj

RESOBJECTS = \
	./resource.obj

OBJECTS += \
	$(DSOOBJECTS) \
	$(RESOBJECTS)
endif

ifneq ($(usingWin32), 1)
LARCHIVE = libInventor.a
endif

SUBDIRS = database interaction nodekits mevis

all: all_ivbin

HEADERS_SUBDIRS = $(SUBDIRS)

install: install_ivlibdso
	$(HEADERS_SUBDIRS_MAKERULE)

COMMONPREF = xxx
$(COMMONTARGS): %: $(COMMONPREF)%
	$(SUBDIRS_MAKERULE)

include $(IVCOMMONRULES)
