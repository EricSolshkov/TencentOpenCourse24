// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SimulateServer.generated.h"


/**
 * Server is abstract interface that simulate a server's behavior, on client.
 * Client can connect to server and send message to server, 
 * receiving message from server.
 * Server is a singleton class, only one instance can be created.
 */
UCLASS()
class TEST54_API USimulateServer : public UObject
{
	GENERATED_BODY()
	
	USimulateServer();
	~USimulateServer();
	
public:
	//USimulateServer(const USimulateServer&) = delete;
	//USimulateServer& operator=(const USimulateServer&) = delete;
	UFUNCTION(Blueprintable, BlueprintCallable)
	static USimulateServer* GetInstance();
	

	UFUNCTION(Blueprintable, BlueprintCallable)
	int GetServerStatus();

	/**
	 * \brief Login to the server.
	 * @param UserName The name of the user.
	 * @param Password The input password. will be hashed before sending to server.
	 * @return the result of the login:
	 * 0 - Exist and correct;
	 * 1 - Password incorrect;
	 * 2 - User not exist.
	 * 3 - User banned
	 */
	UFUNCTION(Blueprintable, BlueprintCallable)
	int Login(const FString& UserName, const FString& Password);

	
	/**
	 * \brief Register a new user to the server.
	 * @param UserName The name of the user.
	 * @param Password The input password. will be hashed before sending to server.
	 * @return the result of the register:
	 * True - Success;
	 * False - User already exist or cannot insert.
	 */
	UFUNCTION(Blueprintable, BlueprintCallable)
	bool Register(const FString& UserName, const FString& Password);
private:
	UPROPERTY()
	TMap<FString, FString> UserDB;

	void ConnectDB();

	void SaveDB();

	/**
	* \brief Query the database to check if the user exists, and if the password is correct.
	* \param UserName The name of the user to query.
	* \param PasswordHash The hashed password of the user. to Avoid transmitting plain text password.
	* \return The result of the query:
	* 0 - Exist and correct;
	* 1 - Password incorrect;
	* 2 - User not exist.
	* 3 - User banned
	*/
	int QueryDB(const FString& UserName, const FString& PasswordHash);

	/**
	 * \brief Insert a new user to the database.
	 * \param UserName The name of the user to insert.
	 * \param PasswordHash The hashed password of the user. to Avoid transmitting plain text password.
	 * \return The result of the insert:
	 * True - Success;
	 * False - User already exist or cannot insert.
	 */
	bool InsertDB(const FString& UserName, const FString& PasswordHash);
};
