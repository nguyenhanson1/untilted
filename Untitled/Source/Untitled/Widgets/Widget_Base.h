// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "Widget_Base.generated.h"

/**
 * 
 */
UCLASS()
class UNTITLED_API UWidget_Base : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** Assign objects of classes that implement IWidgetInterface for display/remove the widget on the screen 
	*	IWidgetInterface* WidgetInterface : A Widget that implements IWidgetInterface
	*
	*/
	void SetMenuInterface(class IMenuInterface* InMenuInterface);

	/** Add this widget to viewport, show mouse cursor, and set the InputMode to be UI Only*/
	void SetUp();

	/** Remove this widget from the viewport, hide cursors, and set the InputMode to be Gameplay Only*/
	void TearDown();

protected:
	/** Stored Widget object that implements IWidgetInterface*/
	IMenuInterface* MenuInterface;

};
