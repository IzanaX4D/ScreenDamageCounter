// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenDamageNumber/Interfaces/Engine/CommitableData.h"
#include "UObject/ObjectMacros.h"


#include "ScreenDamageSlateWidget.generated.h"

USTRUCT(BlueprintType)
struct FScreenDamageParameter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviour)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviour)
	FColor ValueColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviour)
	FText ValueSubtitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviour)
	FColor ValueSubtitleColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviour)
	bool bIgnoreWorldPositionTracking = true;

	/** UI Scaling of the Widget */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviour)
	FVector2D UIScale = FVector2D(1.f, 1.f);
	
};

/** Slate widget for displaying an Damage value to the screen. */
UCLASS(Blueprintable, BlueprintType)
class SCREENDAMAGENUMBER_API UScreenDamageSlateWidget : public UUserWidget, public ICommitableData
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	class UTextBlock* DamageNumberTextLabel;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* SubtitleTextLabel;
	
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidgetAnim))
	UWidgetAnimation* ScreenDamageWidgetAnimation;

	/** Make an floating number value to Rounded integer value upon set.*/
	UPROPERTY(BlueprintReadWrite, Category = Misc, Meta = (Tooltip = "Change the value type display as rounded value."))
	bool bShowRoundValue = true;

	/** Automatically destroy when the anim is done or done the sequence. */
	UPROPERTY(BlueprintReadWrite, Category = Performance)
	bool bAutoDestroy = true;

	/** Set the subtitle text will be. */
	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void SetSubtitle(const FText& SubName, const FColor& SubColor = FColor::White);
	
	/** Set value of the Widget with Color. */
	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void SetValue(const float& Value, const FColor& Color = FColor::White);

	/** Set value from container of the parameter. */
	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void SetFromParam(FScreenDamageParameter Parameter);
		
	/** Condition Design when the slate widget is paste in white color as a Custom Color will run in this event. */
	UFUNCTION(BlueprintNativeEvent, Category = Design)
	void OnColorPaste(const FColor& Color);

	virtual void NativeCommit(UObject* CommitContext) override;
	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

public:
	
	/** Does the Animation is clearing from init. */
	UPROPERTY(BlueprintReadOnly, Category = Misc)
	bool bIsAnimationClear;

	UPROPERTY(BlueprintReadOnly, Category = Misc)
	bool bIgnoreWorldProject = true;
	
	/** World Position of the Widget will be rendered in Viewport. */
	UPROPERTY(BlueprintReadOnly, Category = Misc)
	FVector WorldPosition;

	/** The offset of the world position is Added. */
	UPROPERTY(BlueprintReadWrite, Category = Misc)
	FVector WorldOffsetPosition;
	
	/** Set the UI position follow the World position, if not it will not track/follow the UI position. */
	UFUNCTION(BlueprintCallable, Category = Misc)
	void SetToWorldScreenProject(bool Value){ bIgnoreWorldProject = Value; };

private:

	void UpdateScreenPosition();
};
