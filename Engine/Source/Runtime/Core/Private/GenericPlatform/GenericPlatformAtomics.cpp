// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	GenericPlatformAtomics.cpp: Generic implementations of atomic functions
=============================================================================*/

#include "Core.h"

static_assert(sizeof(FInt128) == 16, "FInt128 size must be 16 bytes.");
static_assert(ALIGNOF(FInt128) == 16, "FInt128 alignment must equals 16.");