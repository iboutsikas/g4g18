// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "UMGEditorPrivatePCH.h"

#include "SZoomPan.h"

#define LOCTEXT_NAMESPACE "UMG"

/////////////////////////////////////////////////////
// SZoomPan

void SZoomPan::Construct(const FArguments& InArgs)
{
	ViewOffset = InArgs._ViewOffset;
	ZoomAmount = InArgs._ZoomAmount;

	ChildSlot
	[
		InArgs._Content.Widget
	];
}

void SZoomPan::OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const
{
	const EVisibility ChildVisibility = ChildSlot.GetWidget()->GetVisibility();
	if ( ArrangedChildren.Accepts(ChildVisibility) )
	{
		const FMargin SlotPadding(ChildSlot.SlotPadding.Get());
		AlignmentArrangeResult XResult = AlignChild<Orient_Horizontal>(AllottedGeometry.Size.X, ChildSlot, SlotPadding, 1);
		AlignmentArrangeResult YResult = AlignChild<Orient_Vertical>(AllottedGeometry.Size.Y, ChildSlot, SlotPadding, 1);

		ArrangedChildren.AddWidget( ChildVisibility, AllottedGeometry.MakeChild(
				ChildSlot.GetWidget(),
				FVector2D(XResult.Offset, YResult.Offset) - ViewOffset.Get(),
				FVector2D(XResult.Size, YResult.Size),
				ZoomAmount.Get()
		) );
	}
}

void SZoomPan::SetContent(const TSharedRef< SWidget >& InContent)
{
	ChildSlot
	[
		InContent
	];
}

#undef LOCTEXT_NAMESPACE
