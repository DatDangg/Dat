#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "FileManager.h"

using namespace std;

FileManager::FileManager() {}

bool FileManager::checkPermission(string username, string typeCheck, Permission fileAccess)
{
    if (typeCheck == "view")
    {
        for (int i = 0; i < fileAccess.viewers.size(); i++)
            if (fileAccess.viewers[i] == username)
                return true;
    }
    else if (typeCheck == "edit")
    {
        for (int i = 0; i < fileAccess.editors.size(); i++)
            if (fileAccess.editors[i] == username)
                return true;
    }
    else if (typeCheck == "delete")
    {
        for (int i = 0; i < fileAccess.deleters.size(); i++)
            if (fileAccess.deleters[i] == username)
                return true;
    }
    else if (typeCheck == "rename")
    {
        for (int i = 0; i < fileAccess.renamers.size(); i++)
            if (fileAccess.renamers[i] == username)
                return true;
    }
    return false;
}

void FileManager::getInfoFile(string dirName, string fileName, FileInfo &fileInfo, Permission &fileAccess)
{
    // string dirName = "tmq";
    // string fileName = "demo1";
    string filePath = "./FileManager/" + dirName + "/" + fileName + "_data.txt";
    cout << filePath;
    ifstream fileStream(filePath);

    if (!fileStream.is_open())
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    string line;
    while (getline(fileStream, line))
    {
        if (line.find("Author:") == 0)
        {
            fileInfo.authorName = line.substr(7);
        }
        else if (line.find("+ View:") == 0)
        {
            string viewersStr = line.substr(8);
            istringstream iss(viewersStr);
            string username;

            while (getline(iss, username, ','))
            {
                // Skip empty usernames
                if (!username.empty())
                {
                    fileAccess.viewers.push_back(username);
                }
            }
        }
        else if (line.find("+ Edit:") == 0)
        {
            string editorsStr = line.substr(8);
            istringstream iss(editorsStr);
            string username;

            while (getline(iss, username, ','))
            {
                if (!username.empty())
                {
                    fileAccess.editors.push_back(username);
                }
            }
        }
        else if (line.find("+ Delete:") == 0)
        {
            string deletersStr = line.substr(10);
            istringstream iss(deletersStr);
            string username;

            while (getline(iss, username, ','))
            {
                if (!username.empty())
                {
                    fileAccess.deleters.push_back(username);
                }
            }
        }
        else if (line.find("+ Rename:") == 0)
        {
            string renamersStr = line.substr(9);
            istringstream iss(renamersStr);
            string username;

            while (getline(iss, username, ','))
            {
                if (!username.empty())
                {
                    fileAccess.renamers.push_back(username);
                }
            }
        }
    }

    fileStream.close();

    // read content
    filePath = "./FileManager/" + dirName + "/" + fileName + ".txt";

    fileStream.open(filePath, ios::out);
    while (getline(fileStream, line))
    {
        fileInfo.content.push_back(line);
    }
    fileStream.close();
}

void FileManager::writeInfoFile(string dirName, string fileName, FileInfo fileInfo, Permission fileAccess)
{
    string filePath = "./FileManager/" + dirName + "/" + fileName + "_data.txt";

    ofstream fileStream(filePath);

    if (!fileStream.is_open())
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    // Write author information
    fileStream << "Author:" << fileInfo.authorName << endl;

    // Write viewers
    fileStream << "+ View:";
    for (const string &viewer : fileAccess.viewers)
    {
        fileStream << viewer << ",";
    }
    fileStream << endl;

    // Write editors
    fileStream << "+ Edit:";
    for (const string &editor : fileAccess.editors)
    {
        fileStream << editor << ",";
    }
    fileStream << endl;

    // Write deleters
    fileStream << "+ Delete:";
    for (const string &deleter : fileAccess.deleters)
    {
        fileStream << deleter << ",";
    }
    fileStream << endl;

    // Write renamers
    fileStream << "+ Rename:";
    for (const string &renamer : fileAccess.renamers)
    {
        fileStream << renamer << ",";
    }
    fileStream << endl;

    fileStream.close();

    // Write content
    filePath = "./FileManager/" + dirName + "/" + fileName + ".txt";

    fileStream.open(filePath, ios::out);
    for (int i = 0; i < fileInfo.content.size(); i++)
    {
        fileStream << fileInfo.content[i] << "\n";
    }
    fileStream.close();
}

void FileManager::createFile(string dirName, string fileName)
{
    fstream newFile;
    string filePath = "./FileManager/" + dirName + "/" + fileName + ".txt";

    newFile.open(filePath);
}

// void FileManager::viewFile(string dirName, string fileName, FileInfo fileInfo, Permission fileAccess)
// {
//     vector<string> content;
//     if (fileInfo.authorName == info.username && checkPermission(info.username, "view", fileAccess))
//     {
//         // display content
//         if (checkPermission(info.username, "edit", fileAccess))
//         {
//             // enable editing
//         }
//     }
//     else
//     {
//         cout << "You don't have permission to access this file.";
//     }
// }

void FileManager::moveFile(string currentDir, string targetDir, string fileName, FileInfo fileInfo, Permission fileAccess)
{
    if (fileInfo.authorName == info.username || checkPermission(info.username, "rename", fileAccess))
    {
        // Move file
        string currentPath = "./FileManager/" + currentDir + "/" + fileName;
        string targetPath = "./FileManager/" + targetDir + "/" + fileName;

        if (rename(currentPath.c_str(), targetPath.c_str()) == 0)
        {
            cout << "File moved successfully.\n";
        }
        else
        {
            cout << "Unable to move file.\n";
        }
    }
    else
    {
        cout << "You don't have permission to move this file.\n";
    }
}

void FileManager::copyFile(string currentDir, string targetDir, string fileName, FileInfo fileInfo, Permission fileAccess)
{
    if (fileInfo.authorName == info.username || checkPermission(info.username, "rename", fileAccess))
    {
        // Copy file
        string currentPath = "./FileManager/" + currentDir + "/" + fileName + ".txt";
        string targetPath = "./FileManager/" + targetDir + "/" + fileName + ".txt";

        ifstream sourceFile(currentPath);
        ofstream targetFile(targetPath);

        if (sourceFile && targetFile)
        {
            targetFile << sourceFile.rdbuf();
            cout << "File copied successfully.\n";
        }
        else
        {
            cout << "Unable to copy file.\n";
        }

        sourceFile.close();
        targetFile.close();
    }
    else
    {
        cout << "You don't have permission to copy this file.\n";
    }
}

void FileManager::renameFile(string dirName, string targetFile, string newFileName, FileInfo fileInfo, Permission fileAccess)
{
    string dirPath = "./FileManager/";
    string oldName = dirPath + dirName + "/" + targetFile + ".txt";
    string newName = dirPath + dirName + "/" + newFileName + ".txt";
    string oldDataName = dirPath + dirName + "/" + targetFile + "_data.txt";
    string newDataName = dirPath + dirName + "/" + newFileName + "_data.txt";

    cout << oldName;
    if (fileInfo.authorName == info.username || checkPermission(info.username, "rename", fileAccess))
    {
        // rename
        if (rename(oldName.c_str(), newName.c_str()) == 0)
        {
            rename(oldDataName.c_str(), newDataName.c_str());
            cout << "File renamed successfully.\n";
        }
        else
        {
            cout << "Unable to rename file. Error: " << strerror(errno) << "\n";
        }
    }
    else
    {
        cout << "You don't have permission to rename this file.";
    }
}

void FileManager::deleteFile(string dirName, string targetFile, FileInfo fileInfo, Permission fileAccess)
{
    string dirPath = "./FileManager/";
    string removeFile = dirPath + dirName + "/" + targetFile + ".txt";

    if (fileInfo.authorName == info.username || checkPermission(info.username, "delete", fileAccess))
    {
        // delete file
        if (remove(removeFile.c_str()) == 0)
        {
            cout << "File deleted successfully.\n";
        }
        else
        {
            cout << "Unable to delete file. Error: " << strerror(errno) << "\n";
        }
    }
    else
    {
        cout << "You don't have permission to delete this file.";
    }
}

void FileManager::permissionsFile(string targetUser, string targetFile, FileInfo fileInfo, Permission fileAccess)
{
    if (fileInfo.authorName == info.username)
    {
        // permission
    }
    else
    {
        cout << "You don't have this right.";
    }
}