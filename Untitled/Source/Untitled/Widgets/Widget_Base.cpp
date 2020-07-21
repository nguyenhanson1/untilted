/** This is A base of Widget class with desired behavior
* for displaying and removing User Interface from the screen
*/


#include "Widget_Base.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"


/** Add this widget to viewport, show mouse cursor, and set the InputMode to be UI Only*/
void UWidget_Base::SetUp()
{
	this->AddToViewport();
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	if (!PlayerController->IsLocalPlayerController()) return;
	
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
}

/** Remove this widget from the viewport, hide cursors, and set the InputMode to be Gameplay Only*/
void UWidget_Base::TearDown()
{
	this->RemoveFromViewport();
	FInputModeGameOnly InputModeData;
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	if (!PlayerController->IsLocalPlayerController()) return;

	FInputModeGameOnly InputModeGame;
	PlayerController->SetInputMode(InputModeGame);

	PlayerController->bShowMouseCursor = false;
}

/** Assign objects of classes that implement IWidgetInterface for display/remove the widget on the screen
*	WidgetInterface : A Widget that implements IWidgetInterface
*/
void UWidget_Base::SetMenuInterface(IMenuInterface* InMenuInterface) {
	MenuInterface = InMenuInterface;
}