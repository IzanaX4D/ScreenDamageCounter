// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define ENGINE_USING_OBJECTPULLING 0
#define ENGINE_WIDGETMAXPOOL 50

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScreenDamageSubsystem.generated.h"

/** Subsystem for managing data Handler on Screen Damage. */
UCLASS()
class SCREENDAMAGENUMBER_API UScreenDamageSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:

	int32 MaxWidgetPool;
	
	/** The Widget object is being pulled register for save performance. */
	TArray<UUserWidget*> SharedWidgetPtr;
	
public:

	// Default Const.
	UScreenDamageSubsystem();
	
	/** Override to control if the Subsystem should be created at all.
	* For example you could only have your system created on servers.
	* It's important to note that if using this is becomes very important to null check whenever getting the Subsystem.
	*
	* Note: This function is called on the CDO prior to instances being created!
	*
	*/
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override;

	/** Pooling the Widget data object. */
	UUserWidget* AddWidgetRegister(UObject* OwnerWidget, TSubclassOf<UUserWidget> WidgetClass);

	/** Get an Pooling Widget data is being available. */
	UUserWidget* GetAvailableWidget(UObject* OwnerWidget);
};
