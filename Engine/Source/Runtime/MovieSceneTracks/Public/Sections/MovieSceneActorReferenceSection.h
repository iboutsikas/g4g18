// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MovieSceneSection.h"
#include "IKeyframeSection.h"
#include "MovieSceneActorReferenceSection.generated.h"

/**
 * A single actor reference point section
 */
UCLASS( MinimalAPI )
class UMovieSceneActorReferenceSection
	: public UMovieSceneSection
	, public IKeyframeSection<FGuid>
{
	GENERATED_UCLASS_BODY()
public:
	/**
	 * Updates this section
	 *
	 * @param Position	The position in time within the movie scene
	 */
	FGuid Eval( float Position ) const;

	// IKeyframeSection interface.

	void AddKey( float Time, const FGuid& Value, EMovieSceneKeyInterpolation KeyInterpolation );
	bool NewKeyIsNewData(float Time, const FGuid& Value) const;
	bool HasKeys( const FGuid& Value ) const;
	void SetDefault( const FGuid& Value );

	/**
	 * UMovieSceneSection interface 
	 */
	virtual void MoveSection(float DeltaPosition, TSet<FKeyHandle>& KeyHandles) override;
	virtual void DilateSection(float DilationFactor, float Origin, TSet<FKeyHandle>& KeyHandles) override;
	virtual void GetKeyHandles(TSet<FKeyHandle>& OutKeyHandles, TRange<float> TimeRange) const override;
	virtual TOptional<float> GetKeyTime( FKeyHandle KeyHandle ) const override;
	virtual void SetKeyTime( FKeyHandle KeyHandle, float Time ) override;

	/**
	 * @return The integral curve on this section
	 */
	FIntegralCurve& GetActorReferenceCurve() { return ActorGuidIndexCurve; }

	virtual void PreSave() override;
	virtual void PostLoad() override;

private:
	/** Curve data */
	UPROPERTY()
	FIntegralCurve ActorGuidIndexCurve;

	TArray<FGuid> ActorGuids;

	UPROPERTY()
	TArray<FString> ActorGuidStrings;
};