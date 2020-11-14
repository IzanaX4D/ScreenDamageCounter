// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenDamageSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ScreenDamageNumber/Widgets/ScreenDamageSlateWidget.h"

UScreenDamageSubsystem::UScreenDamageSubsystem()
{
	// Set max Pool for widget will be initialize. 
	MaxWidgetPool = ENGINE_WIDGETMAXPOOL;
}

void UScreenDamageSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

#if WITH_EDITORONLY_DATA && ENGINE_USING_OBJECTPULLING
	/** Creating an Pooling from the widget. */
	
	
#endif

	
}

void UScreenDamageSubsystem::Deinitialize()
{
	/** Clearing/Cleanup the Widget pointer. */
	for(UUserWidget* WidgetPtr : SharedWidgetPtr)
		WidgetPtr->RemoveFromViewport();
	
	SharedWidgetPtr.Empty();
}

UUserWidget* UScreenDamageSubsystem::AddWidgetRegister(UObject* OwnerWidget, TSubclassOf<UUserWidget> WidgetClass)
{
	/** Create an pooling object for the Widget. */
	UUserWidget* WidgetObject = CreateWidget(Cast<APlayerController>(OwnerWidget), WidgetClass);

	// If its failed force to null.
	if(WidgetObject == nullptr)
		return nullptr;
	else
	{
		// Adding an Smart Pointer reference.
		if(WidgetObject->AddToPlayerScreen())
			SharedWidgetPtr.Add(WidgetObject);
		return WidgetObject;
	}
}

UUserWidget* UScreenDamageSubsystem::GetAvailableWidget(UObject* OwnerWidget)
{
	UScreenDamageSlateWidget* CachedSlateWidget = nullptr;

	if(SharedWidgetPtr.Num() > 0)
	{
		UUserWidget* TSharePtrWidget = nullptr;

		/** Find the Idle one widget. */
		for (int Index = 0; Index < SharedWidgetPtr.Num(); ++Index)
		{
			TSharePtrWidget = SharedWidgetPtr[Index];
			UScreenDamageSlateWidget* CachedWidget = Cast<UScreenDamageSlateWidget>(TSharePtrWidget);
			if(CachedWidget)
			{
				if(CachedWidget->bIsAnimationClear && CachedWidget->GetOwningPlayer() == Cast<APlayerController>(OwnerWidget))
				{
					CachedSlateWidget = CachedWidget;
					break;
				}
			}
		}
	}

#if WITH_EDITORONLY_DATA
	// Check for the widget
	if(CachedSlateWidget)
		UE_LOG(LogTemp, Warning, TEXT("Found cached slate widget. "))
#endif

	return CachedSlateWidget;
}

