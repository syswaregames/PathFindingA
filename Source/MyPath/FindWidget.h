// Copyright Patrick Carvalho All Rights Reserved.
// sysware@sysware.com.br
// 

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "MyPathBlockGrid.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateTypes.h"
#include "MyPathTask.h"

#include "FindWidget.generated.h"

UCLASS()
class MYPATH_API UFindWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UButton* FindButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ClearButton;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CheckHeuristic;

	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ComboHeuristic;
	
	AMyPathBlockGrid* Grid;

	AMyPathBlock* nStart;
	AMyPathBlock* nEnd;
    
    UPROPERTY()
    class UMaterialInstance* OrangeMaterial;

	virtual void NativeOnInitialized() override;
	void LinkNodes(AMyPathBlock *n1, AMyPathBlock *n2);

	void Setup();

	bool GetHeuristic();


protected:
	UFUNCTION()
	void OnFindClicked();
	
	UFUNCTION()
	void OnClearClicked();

	UFUNCTION()
	void OnCheckClicked(bool bIsChecked);

	bool bHeuristic = true;

};
