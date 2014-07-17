// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PropertyEditorModule.h"
#include "LandscapeEditorDetailCustomization_Base.h"

// Forward declarations
class FLandscapeEditorDetailCustomization_NewLandscape;
class FLandscapeEditorDetailCustomization_ResizeLandscape;
class FLandscapeEditorDetailCustomization_CopyPaste;
class FLandscapeEditorDetailCustomization_MiscTools;
class FLandscapeEditorDetailCustomization_AlphaBrush;
class FLandscapeEditorDetailCustomization_TargetLayers;

class FLandscapeEditorDetails : public FLandscapeEditorDetailCustomization_Base
{
public:
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IDetailCustomization> MakeInstance();

	/** IDetailCustomization interface */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

protected:
	static FText GetLocalizedName(FString Name);

	static EVisibility GetTargetLandscapeSelectorVisibility();
	static FText GetTargetLandscapeName();
	static TSharedRef<SWidget> GetTargetLandscapeMenu();
	static void OnChangeTargetLandscape(TWeakObjectPtr<ULandscapeInfo> LandscapeInfo);

	FText GetCurrentToolName() const;
	FSlateIcon GetCurrentToolIcon() const;
	TSharedRef<SWidget> GetToolSelector();
	bool GetToolSelectorIsVisible() const;
	EVisibility GetToolSelectorVisibility() const;
	void OnChangeTool(FName ToolName);
	bool IsToolEnabled(FName ToolName) const;

	FText GetCurrentBrushName() const;
	FSlateIcon GetCurrentBrushIcon() const;
	TSharedRef<SWidget> GetBrushSelector();
	bool GetBrushSelectorIsVisible() const;
	void OnChangeBrushSet(FName BrushSetName);
	bool IsBrushSetEnabled(FName BrushSetName) const;

	FText GetCurrentBrushFalloffName() const;
	FSlateIcon GetCurrentBrushFalloffIcon() const;
	TSharedRef<SWidget> GetBrushFalloffSelector();
	bool GetBrushFalloffSelectorIsVisible() const;
	void OnChangeBrush(FName BrushName);
	bool IsBrushActive(FName BrushName) const;

	TSharedPtr<FUICommandList> CommandList;

	TSharedPtr<FLandscapeEditorDetailCustomization_NewLandscape> Customization_NewLandscape;
	TSharedPtr<FLandscapeEditorDetailCustomization_ResizeLandscape> Customization_ResizeLandscape;
	TSharedPtr<FLandscapeEditorDetailCustomization_CopyPaste> Customization_CopyPaste;
	TSharedPtr<FLandscapeEditorDetailCustomization_MiscTools> Customization_MiscTools;
	TSharedPtr<FLandscapeEditorDetailCustomization_AlphaBrush> Customization_AlphaBrush;
	TSharedPtr<FLandscapeEditorDetailCustomization_TargetLayers> Customization_TargetLayers;
};
