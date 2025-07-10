// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HWPawn.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FInputActionValue;
#ifdef HW07_HWPawn_generated_h
#error "HWPawn.generated.h already included, missing '#pragma once' in HWPawn.h"
#endif
#define HW07_HWPawn_generated_h

#define FID_HW07_Source_HW07_Public_HWPawn_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsHitGround); \
	DECLARE_FUNCTION(execApplyGravity); \
	DECLARE_FUNCTION(execRoll); \
	DECLARE_FUNCTION(execFlight); \
	DECLARE_FUNCTION(execLook); \
	DECLARE_FUNCTION(execMove);


#define FID_HW07_Source_HW07_Public_HWPawn_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAHWPawn(); \
	friend struct Z_Construct_UClass_AHWPawn_Statics; \
public: \
	DECLARE_CLASS(AHWPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/HW07"), NO_API) \
	DECLARE_SERIALIZER(AHWPawn)


#define FID_HW07_Source_HW07_Public_HWPawn_h_19_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AHWPawn(AHWPawn&&); \
	AHWPawn(const AHWPawn&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AHWPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AHWPawn); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AHWPawn) \
	NO_API virtual ~AHWPawn();


#define FID_HW07_Source_HW07_Public_HWPawn_h_16_PROLOG
#define FID_HW07_Source_HW07_Public_HWPawn_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_HW07_Source_HW07_Public_HWPawn_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_HW07_Source_HW07_Public_HWPawn_h_19_INCLASS_NO_PURE_DECLS \
	FID_HW07_Source_HW07_Public_HWPawn_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> HW07_API UClass* StaticClass<class AHWPawn>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_HW07_Source_HW07_Public_HWPawn_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
