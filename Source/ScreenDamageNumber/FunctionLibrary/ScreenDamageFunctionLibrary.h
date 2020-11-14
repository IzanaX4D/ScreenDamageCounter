// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ScreenDamageNumber/SubSystem/ScreenDamageSubsystem.h"
#include "ScreenDamageNumber/Widgets/ScreenDamageSlateWidget.h"

#include "ScreenDamageFunctionLibrary.generated.h"

/** Function library for showing the damage counter to show on the screen. */
UCLASS(BlueprintType)
class SCREENDAMAGENUMBER_API UScreenDamageFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/** Showing an Damage Screen on HUD Canvas (Object Pooling Support). */
	UFUNCTION(BlueprintCallable, Category = Screening, Meta = (WorldContext = "WorldContext"))
	static void ShowScreenDamage(UObject* WorldContext, UObject* OwnerWidget, TSubclassOf<UScreenDamageSlateWidget> ClassWidget, FVector WorldPosition, const float& Value, const FText& SubtitleText, const FLinearColor& Color, bool bUseWorldSpace = true);

	UFUNCTION(BlueprintCallable, Category = Screening, Meta = (WorldContext = "WorldContext"))
	static void ShowScreenDamageWithParam(UObject* WorldContext, UObject* OwnerWidget, TSubclassOf<UScreenDamageSlateWidget> ClassWidget, FVector WorldPosition, const FScreenDamageParameter& Parameter);
};
