// Fill out your copyright notice in the Description page of Project Settings.
#include "SimulateServer.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Misc/SecureHash.h"
#include "Dom/JsonObject.h"

static USimulateServer* Instance = nullptr;


USimulateServer::USimulateServer()
{
	ConnectDB();
}

USimulateServer::~USimulateServer()
{
	SaveDB();
}

USimulateServer* USimulateServer::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<USimulateServer>();
		Instance->AddToRoot();
	}
	return Instance;
}

int USimulateServer::GetServerStatus()
{
	return 0;
}

int USimulateServer::Login(const FString& UserName, const FString& Password)
{
	if (UserName.IsEmpty() || Password.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Passing empty string to Register"));
		return 3;
	}
	const FString PasswordHash = FMD5::HashAnsiString(*Password);
	const int query = QueryDB(UserName, PasswordHash);
	return query;
}

void USimulateServer::ConnectDB()
{
	// read from a json file, just to simulate the database
	FString JsonString;
	// if not exist create a empty json file
	if (!FPaths::FileExists(TEXT("UserDB.json")))
	{
		FFileHelper::SaveStringToFile(TEXT("{}"), TEXT("UserDB.json"));
	}
	UserDB.Empty();
	// Load json object as a map to create UserDB
	FFileHelper::LoadFileToString(JsonString, TEXT("UserDB.json"));
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	TSharedPtr<FJsonObject> Root;
	if(FJsonSerializer::Deserialize<TCHAR>(JsonReader, Root))
	{
		if (Root->HasField(FString("Users")))
		{
			const TArray<TSharedPtr<FJsonValue>> Users = Root->GetArrayField(FString("Users"));
			for (const TSharedPtr<FJsonValue>& User : Users)
			{
				const TSharedPtr<FJsonObject> UserObj = User->AsObject();
				const FString UserName = UserObj->GetStringField(FString("UserName"));
				const FString PasswordHash = UserObj->GetStringField(FString("PasswordHash"));
				UserDB.Add(UserName, PasswordHash);
			}
		}
	}
	
}

void USimulateServer::SaveDB()
{
	// 创建一个 FJsonObject 对象来存储用户数据
	TSharedPtr<FJsonObject> Root = MakeShareable(new FJsonObject);

	// 创建一个数组来存储用户数据
	TArray<TSharedPtr<FJsonValue>> UsersArray;

	// 将 UserDB 中的每个用户数据添加到数组中
	for (const auto& Pair : UserDB)
	{
		TSharedPtr<FJsonObject> UserObj = MakeShareable(new FJsonObject);
		UserObj->SetStringField(TEXT("UserName"), Pair.Key);
		UserObj->SetStringField(TEXT("PasswordHash"), Pair.Value);
		UsersArray.Add(MakeShareable(new FJsonValueObject(UserObj)));
	}

	// 将用户数据数组添加到 Root 对象中
	Root->SetArrayField(TEXT("Users"), UsersArray);

	// 序列化 Root 对象为字符串
	FString JsonString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(Root.ToSharedRef(), JsonWriter);

	// 将字符串保存到文件中
	FFileHelper::SaveStringToFile(JsonString, TEXT("UserDB.json"));
}

bool USimulateServer::Register(const FString& UserName, const FString& Password)
{
	if (UserName.IsEmpty() || Password.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Passing empty string to Register"));
		return false;
	}
	// Hash the Password, and try to insert to the database
	const FString PasswordHash = FMD5::HashAnsiString(*Password);
	const bool InsertResult = InsertDB(UserName, PasswordHash);
	return InsertResult;
}

int USimulateServer::QueryDB(const FString& UserName, const FString& PasswordHash)
{
	// check if hashed password is identical to the one in the database
	if (UserDB.Contains(UserName))
	{
		if (UserDB[UserName] == PasswordHash)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 2;
	}
}

bool USimulateServer::InsertDB(const FString& UserName, const FString& PasswordHash)
{
	// first check if the user already exists
	if (UserDB.Contains(UserName))
	{
		return false;
	}
	else
	{
		UserDB.Add(UserName, PasswordHash);
		SaveDB();
		return true;
	}
}
	
