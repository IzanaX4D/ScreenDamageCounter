// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenDamageFunctionLibrary.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ScreenDamageNumber/SubSystem/ScreenDamageSubsystem.h"

void UScreenDamageFunctionLibrary::ShowScreenDamage(UObject* WorldContext, UObject* OwnerWidget, TSubclassOf<UScreenDamageSlateWidget> ClassWidget, FVector WorldPosition, const float& Value, const FText& SubtitleText, const FLinearColor& Color, bool bUseWorldSpace)
{
	/** GETTING AN THE SUBSYSTEM */
	static UScreenDamageSubsystem* SDSub = nullptr;
	if(SDSub == nullptr)
		SDSub = UGameplayStatics::GetGameInstance(WorldContext)->GetSubsystem<UScreenDamageSubsystem>();
	/** ============================== */
	
	// Check once again.
	if(SDSub == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find an SDF subsystem, cannot retrying. check SourceCode."))
		return;
	}
	/** ============================== */
	
	APlayerController* PC = Cast<APlayerController>(OwnerWidget);
	UScreenDamageSlateWidget* CachedSlateWidget = Cast<UScreenDamageSlateWidget>(CreateWidget(PC, ClassWidget));
	if(CachedSlateWidget == nullptr)
		return;
	else
	{
		// Adding to the Screen. 
		CachedSlateWidget->AddToPlayerScreen();
		
		CachedSlateWidget->WorldPosition = WorldPosition;
		CachedSlateWidget->SetSubtitle(SubtitleText, FColor(Color));
		CachedSlateWidget->SetValue(Value, Color.ToFColor(false));
	}

	/** TODO : Using an Optimize Object Pooling in if it's can*/
}

void UScreenDamageFunctionLibrary::ShowScreenDamageWithParam(UObject* WorldContext, UObject* OwnerWidget, TSubclassOf<UScreenDamageSlateWidget> ClassWidget, FVector WorldPosition, const FScreenDamageParameter& Parameter)
{
	/** GETTING AN THE SUBSYSTEM */
	static UScreenDamageSubsystem* SDSub = nullptr;
	if(SDSub == nullptr)
		SDSub = UGameplayStatics::GetGameInstance(WorldContext)->GetSubsystem<UScreenDamageSubsystem>();
	/** ============================== */
	
	// Check once again.
	if(SDSub == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find an SDF subsystem, cannot retrying. check SourceCode."))
          return;
	}
	/** ============================== */

	APlayerController* PC = Cast<APlayerController>(OwnerWidget);
	UScreenDamageSlateWidget* CachedSlateWidget = Cast<UScreenDamageSlateWidget>(CreateWidget(PC, ClassWidget));
	if(CachedSlateWidget == nullptr)
		return;
	else
	{
		// Adding to the Screen. 
		CachedSlateWidget->AddToPlayerScreen();

		CachedSlateWidget->SetValue(Parameter.Value,Parameter.ValueColor);
		CachedSlateWidget->SetSubtitle(Parameter.ValueSubtitle, Parameter.ValueSubtitleColor);
		CachedSlateWidget->bIgnoreWorldProject = Parameter.bIgnoreWorldPositionTracking;
		CachedSlateWidget->SetDesiredSizeInViewport(Parameter.UIScale);
	}

}
