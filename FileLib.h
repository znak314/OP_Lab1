#pragma once
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<fstream>
#include<string>




using namespace std;

int is_exist(string Name);

void FileCreate(string Name);
void FileCreate(char* Name, char* NewName);

void FileFill(string Name);
void FileFill(char* Name);

void FillNewFile(string OldFile, string NewFile);
void FillNewFile(char* OldFile, char* NewFile);

void PrintFile(string Name);
void PrintFile(char* Name);

void file_append(string Name);
void file_append(char* Name);


void ReFillFile(string Name);
void ReFillFile(char* Name);
