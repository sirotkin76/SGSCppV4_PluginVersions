// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "Graph/SGSCppV4_CustomGraphRuntimeGraph.h"
#include <functional>

#include "Data/SGSCppV4_GraphRuntimeStuctures.h"
#include "SGSCppV4_CustomGraphAsset.generated.h"

UCLASS(BlueprintType)
class SIRGASSYSTEMRUNTIME_API USGSCppV4_CustomGraphAsset : public UObject {
    GENERATED_BODY()

public:
    // 
    UPROPERTY()
    USGSCppV4_CustomGraphRuntimeGraph* Graph = nullptr;
    
    // 
    UPROPERTY(EditAnywhere, Category="SGSCppGraph")
    FString SGSCppCustomGraphName = TEXT("Enter name here");
    
    UFUNCTION()
    USGSCppCustomGraphRuntimeNode* SGSCppFindNodeUseUniqueIndex(int32 UniqueIndexNode) ;

    UFUNCTION()
    FOutputData SGSCppFindOutputDataUseIndex(int32 UniqueIndexNode);
    
    UFUNCTION(BlueprintCallable, Category = "SGSCppGraph")
    USGSCppV4_CustomGraphRuntimeGraph* GetSGSCppGraph() const { return Graph; };
    
    UFUNCTION()
    FOutputData SGSCppFindDataUseUniqueIndexNode(int32 UniqueIndexNodeInGraphForFindData);

    UFUNCTION()
    FOutputData SGSCppFindDataUseNode(USGSCppCustomGraphRuntimePin * SGSCppCustomGraphRuntimePinLocal);

    //
    UFUNCTION()
    FOutputPinDataV2 SGSCppGetOutpinDataUseUniqueIndexNode(int32 UniqueIndexNodeInGraphForFindData);
    
    //
    UFUNCTION(Category = "SGSCppGraph", meta = (GameplayTagFilter = "SGSCppGraph.Output"))
    FOutputData SGSCppFindDataUseFindTag(FGameplayTag InInputTag);

    // Данная функция выводит данные первой ноды, которая подключена к ноде Start.
    // Нода Start является нулевой нодой, а первая нода - это та которая подключена к ноде Start.
    // This function outputs data from the first node connected to the start node.
    // The start node is the zero node, and the first node is the one connected to the start node.
    UFUNCTION(BlueprintCallable, Category = "SGSCppGraph", meta = (GameplayTagFilter = "SGSCppGraph.Output"))
    int32 SGSCppGetUniqueIndexFirstNode();

    // Возвращает наименование главного графика.
    // Returns the name of the Graph asset. 
    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    FString SGSCppGetCustomGraphName() { return SGSCppCustomGraphName; };
    
    // Функция ищет ноду по переменной "UniqueIndexNodeInGraph" в графике. Затем проверяет относится ли нода к типу “Continue node”.
    // Если нода будет найдена, то функция выводит все данные из ноды.
    // The function searches for a node in the graph using the "UniqueIndexNodeInGraph" variable. It then checks whether the node is of the "Continue node" type.
    // If the node is found, the function outputs all data from the node.
    UFUNCTION()
    void SGSCppFindNode_GetAttrData_00_Pure(int32 UniqueIndexNode, FText& OutTitle, FText& OutDescription, TArray<FGameplayTag>& OutOutputTags, ESGSCppV4_CustomGraphNodeType& OutNodeType) ;
    
    // Функция ищет ноду по переменной "UniqueIndexNodeInGraph" в графике. Затем проверяет относится ли нода к типу “Continue node”.
    // Затем в переменной "OutputTags" находим ноду "ResponceTag" и выводим данные найденой ноды. 
    // The function searches for a node in the graph using the "UniqueIndexNodeInGraph" variable. It then checks whether the node is of the "Continue node" type.
    // Then, in the "OutputTags" variable, we find the "ResponseTag" node and output the data for the found node.
    UFUNCTION(BlueprintCallable, Category = "SGSCppGraph", meta = (GameplayTagFilter = "SGSCppGraph.Output"))
    void SGSCppFindNode_GetAttrData_00_UseTag(int32 UniqueIndexNodeInGraphForFindData,
        FGameplayTag ResponceTag, int32& OutUniqueIndexNodeInGraph, FText& OutTitle, FText& OutDescription, TArray<FGameplayTag>& OutOutputTags, ESGSCppV4_CustomGraphNodeType& OutNodeType);

    // Функция находит ноду по переменной "UniqueIndexNodeInGraph" и выводит базовые атрибуты данной ноды. 
    // The function finds a node by the variable "UniqueIndexNodeInGraph" and displays the basic attributes of this node.
    UFUNCTION(BlueprintCallable, Category = "SGSCppGraph")
    void SGSCppFindNode_GetAttrData_00(int32 UniqueIndexNodeInGraphForFindData, FText& Title, FText& Description, TArray<FGameplayTag>& OutputTags, ESGSCppV4_CustomGraphNodeType& NodeType);

    // Функция находит End node по уникальному индексу и отображает его параметры.
    // Finds the end node by a unique index and displays the parameters.
    UFUNCTION(BlueprintCallable, Category = "SGSCppGraph")
    void SGSCppFindNode_END_GetAttrData_01(int32 UniqueIndexNodeInGraphForFindData, FGameplayTag& TagForFindNode, FString& CustomAction, UPrimaryDataAsset*& PrimaryDataAsset);

    // This function searches the ArrInt array and displays the result.
    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    void SGSCppFindNodeUse_TagForFindNode(FGameplayTag TagForFindNode,int32& UniqueIndexNodeInGraphForFindData);
    
    // Эта функция выполняет поиск в массиве ArrInt и отображает результат.
    // This function searches the ArrInt array and displays the result.
    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    int32 SGSCppFindNodeContinueGetData_01_FindArrInt(int32 UniqueIndexNode, FName FindNameInArr);
    
    // Эта функция выполняет поиск в массиве ArrInt и отображает результат.
    // This function searches the ArrInt array and displays the result.
    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    float SGSCppFindNodeContinueGetData_01_FindArrFloat(int32 UniqueIndexNode, FName FindNameInArr);

    // Эта функция выполняет поиск в массиве ArrText и отображает результат.
    // This function searches the ArrText array and displays the result.
    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    FText SGSCppFindNodeContinueGetData_01_FindArrText(int32 UniqueIndexNode, FName FindNameInArr);

    // Эта функция выполняет поиск в массиве ArrName и отображает результат.
    // This function searches the ArrName array and displays the result.
    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    FName SGSCppFindNodeContinueGetData_01_FindArrName(int32 UniqueIndexNode, FName FindNameInArr);

    // Эта функция выполняет поиск в массиве ArrGameplayTags и отображает результат.
    // This function searches the ArrGameplayTags array and displays the result.
    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    FGameplayTagContainer SGSCppFindNodeContinueGetData_01_FindArrGameplayTags(int32 UniqueIndexNode, FName FindNameInArr);

    // Эта функция выполняет поиск в массиве ArrUObject и отображает результат.
    // This function searches the ArrUObject array and displays the result.
    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    TSoftObjectPtr<UObject> SGSCppFindNodeContinueGetData_01_FindArrUObject(int32 UniqueIndexNode, FName FindNameInArr);

    // Эта функция выполняет поиск в массиве Class UObject и отображает результат.
    // This function searches the ArrClassUObject array and displays the result.
    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    TSubclassOf<UObject> SGSCppFindNodeContinueGetData_01_FindArrClassUObject(int32 UniqueIndexNode, FName FindNameInArr);


    // Функция находит End node по уникальному индексу и отображает его параметры.
    // Finds the end node by a unique index and displays the parameters.
    UFUNCTION(BlueprintCallable, Category = "SGSCppGraph")
    void SGSCppFindNode_ContinueDataAsset_GetAttrData_01(int32 UniqueIndexNodeInGraphForFindData, USGSCppV4_DataAsset_Attr*& SGSCppDataAssetAttrV3, UPrimaryDataAsset*& PrimaryDataAsset);



    
public: // Our interface
    void SetPreSaveListener(std::function<void()> onPreSaveListener) { _onPreSaveListener = onPreSaveListener; }

    UFUNCTION()
    TArray<USGSCppCustomGraphRuntimePin*> GetSGSCppOutputConnectionPins(int32 NodeIndex);


public: // UObject interface
    virtual void PreSave(FObjectPreSaveContext saveContext) override;

private: // Members
    std::function<void()> _onPreSaveListener = nullptr;
};
