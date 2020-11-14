// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenDamageSlateWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UScreenDamageSlateWidget::OnColorPaste_Implementation(const FColor& Color)
{
	if(DamageNumberTextLabel == nullptr)
		return;
	DamageNumberTextLabel->SetColorAndOpacity(FLinearColor(Color));
}

void UScreenDamageSlateWidget::SetSubtitle(const FText& SubName, const FColor& SubColor)
{
	if(SubtitleTextLabel == nullptr)
		return;
	SubtitleTextLabel->SetText(SubName);
	SubtitleTextLabel->SetColorAndOpacity(FLinearColor(SubColor));
}

void UScreenDamageSlateWidget::SetValue(const float& Value, const FColor& Color)
{
	// check component. 
	if(DamageNumberTextLabel == nullptr)
		return;

	DamageNumberTextLabel->SetText(FText::FromString(FString::FromInt(bShowRoundValue ? FMath::RoundToInt(Value) : Value)));
	if(Color != FColor::White)
	{
		DamageNumberTextLabel->SetColorAndOpacity(FLinearColor(Color));
		if(SubtitleTextLabel)
			SubtitleTextLabel->SetColorAndOpacity(FLinearColor(Color));
	}
	else
		OnColorPaste(Color);

	// Commit Widget action. 
	NativeCommit(this);
}

void UScreenDamageSlateWidget::SetFromParam(FScreenDamageParameter Parameter)
{
	SetSubtitle(Parameter.ValueSubtitle);
	SetValue(Parameter.Value,Parameter.ValueColor);
}

void UScreenDamageSlateWidget::NativeCommit(UObject* CommitContext)
{
	// Play the animation once commiting data. 
	if(ScreenDamageWidgetAnimation != nullptr)
		PlayAnimation(ScreenDamageWidgetAnimation);

	// Updating the Screen position for adjustment.
	UpdateScreenPosition();
	
}

void UScreenDamageSlateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Animation clear markings.
	bIsAnimationClear = false;

	// Set as Empty subtitle. 
	if(SubtitleTextLabel)
		SubtitleTextLabel->SetText(FText::GetEmpty());
}

void UScreenDamageSlateWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	/** Updating the world position Screen Projection. */
	if(!bIgnoreWorldProject && !bIsAnimationClear)
		UpdateScreenPosition();
}

void UScreenDamageSlateWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);
	bIsAnimationClear = true;

	if(bAutoDestroy)
		RemoveFromViewport();
}

void UScreenDamageSlateWidget::UpdateScreenPosition()
{
	FVector2D ScreenPos;
	UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), WorldPosition + WorldOffsetPosition, ScreenPos);
	SetPositionInViewport(ScreenPos, true);
}
