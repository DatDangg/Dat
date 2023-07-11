#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "FileManager.h"

using namespace std;

FileManager::FileManager() {}

void FileManager::setUserInfo(string &username)
{
    info.username = username;
}

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
            string viewersStr = line.substr(7);
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
            string editorsStr = line.substr(7);
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
            string deletersStr = line.substr(9);
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
    string filePath = "./FileManager/" + dirName + "/" + fileName + ".txt";
    ofstream newFile(filePath);
    // string file_Path = "./FileManager/" + dirName + "/" + fileName + "_data.txt";
    // ofstream newFile_(file_Path);
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
/**
 * @brief the function will check the user's permissions. If authorized, the user can move the file
 * !Message error:
 * 1: success
 * -1: do not have this right
 * -2: Unable to move file. Error: strerror(errno)
 *
 * @param currentDir
 * @param targetDir
 * @param fileName
 * @param fileInfo
 * @param fileAccess
 */
int FileManager::moveFile(string currentDir, string targetDir, string fileName, FileInfo fileInfo, Permission fileAccess)
{

    if (fileInfo.authorName == info.username || checkPermission(info.username, "rename", fileAccess))
    {
        // Move file
        string currentPath = "./FileManager/" + currentDir + "/" + fileName + ".txt";
        string targetPath = "./FileManager/" + targetDir + "/" + fileName + ".txt";
        string currentDataPath = "./FileManager/" + currentDir + "/" + fileName + "_data.txt";
        string targetDataPath = "./FileManager/" + targetDir + "/" + fileName + "_data.txt";
        if (rename(currentPath.c_str(), targetPath.c_str()) == 0)
        {
            rename(currentDataPath.c_str(), targetDataPath.c_str());
            return 1;
        }
        else
            return -2;
    }
    return -1;
}

/**
 * @brief the function will check the user's permissions. If authorized, the user can copy the file
 * !Message error:
 * 1: success
 * -1: do not have this right
 * -2: Unable to copy file. Error: strerror(errno)
 *
 * @param currentDir
 * @param targetDir
 * @param fileName
 * @param fileInfo
 * @param fileAccess
 */
int FileManager::copyFile(string currentDir, string targetDir, string fileName, FileInfo fileInfo, Permission fileAccess)
{
    
    if (fileInfo.authorName == info.username || checkPermission(info.username, "rename", fileAccess))
    {
        // Copy file
        string currentPath = "./FileManager/" + currentDir + "/" + fileName + ".txt";
        string targetPath = "./FileManager/" + targetDir + "/" + fileName + ".txt";
        string currentDataPath = "./FileManager/" + currentDir + "/" + fileName + "_data.txt";
        string targetDataPath = "./FileManager/" + targetDir + "/" + fileName + "_data.txt";

        ifstream sourceFile(currentPath);
        ofstream targetFile(targetPath);
        ifstream sourceDataFile(currentDataPath);
        ofstream targetDataFile(targetDataPath);

        if (sourceFile.is_open() && targetFile.is_open() && sourceDataFile.is_open() && targetDataFile.is_open())
        {
            targetFile << sourceFile.rdbuf();

            targetDataFile << sourceDataFile.rdbuf();

            sourceFile.close();
            targetFile.close();
            sourceDataFile.close();
            targetDataFile.close();

            return 1;
        }
        else
        {
            return -2;
        }
    }
    return -1;
}

/**
 * @brief the function will check the user's permissions. If authorized, the user can rename file the file
 * !Message error:
 * 1: success
 * -1: do not have this right
 * -2: Unable to rename file. Error: strerror(errno)
 *
 * @param dirName
 * @param targetFile
 * @param newFileName
 * @param fileInfo
 * @param fileAccess
 */
int FileManager::renameFile(string dirName, string targetFile, string newFileName, FileInfo fileInfo, Permission fileAccess)
{
    string dirPath = "./FileManager/";
    string oldName = dirPath + dirName + "/" + targetFile + ".txt";
    string newName = dirPath + dirName + "/" + newFileName + ".txt";
    string oldDataName = dirPath + dirName + "/" + targetFile + "_data.txt";
    string newDataName = dirPath + dirName + "/" + newFileName + "_data.txt";

    // cout << oldName;
    if (fileInfo.authorName == info.username || checkPermission(info.username, "rename", fileAccess))
    {
        // rename
        if (rename(oldName.c_str(), newName.c_str()) == 0)
        {
            rename(oldDataName.c_str(), newDataName.c_str());
            return 1;
        }
        else
        {
            return -2;
        }
    }
    return -1;
}

/**
 * @brief the function will check the user's permissions. If authorized, the user can delete the file
 * !Message error:
 * 1: success
 * -1: do not have this right
 * -2: Unable to delete file. Error: strerror(errno)
 * @param dirName
 * @param targetFile
 * @param fileInfo
 * @param fileAccess
 */
int FileManager::deleteFile(string dirName, string targetFile, FileInfo fileInfo, Permission fileAccess)
{
    string dirPath = "./FileManager/";
    string removeFile = dirPath + dirName + "/" + targetFile + ".txt";
    string removeDataFile = dirPath + dirName + "/" + targetFile + "_data.txt";

    if (fileInfo.authorName == info.username || checkPermission(info.username, "delete", fileAccess))
    {
        // delete file
        if (remove(removeFile.c_str()) == 0)
        {
            remove(removeDataFile.c_str());
            return 1;
        }
        else
            return -2;
    }
    return -1;
}

/**
 * @brief the function will check the user's permissions and check the username. if the user exists, it will push to the vector, then save it back to the file,
 * !Message error:
 * 1: successful
 * -1: don't have this right.
 * -2:
 * @param targetUser
 * @param targetFile
 * @param permission
 * @param fileInfo
 * @param fileAccess
 */
int FileManager::permissionsFile(string targetUser, string targetFile, vector<string> permission, FileInfo &fileInfo, Permission &fileAccess)
{
    
    if (fileInfo.authorName == info.username)
    {
        // permission
        if (checkInfo(targetUser))
        {
            for (int i = 0; i < permission.size(); i++)
            {
                if (permission[i] == "view")
                    fileAccess.viewers.push_back(targetUser);
                if (permission[i] == "edit")
                    fileAccess.editors.push_back(targetUser);
                if (permission[i] == "delete")
                    fileAccess.deleters.push_back(targetUser);
                if (permission[i] == "rename")
                    fileAccess.renamers.push_back(targetUser);
            }
            return 1;
        }
    }
    return -1;
}

vector<string> PrintFiles(const string& folderPath)
{
    WIN32_FIND_DATAA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    string searchPath = folderPath + "\\*";

    hFind = FindFirstFileA(searchPath.c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "Cannot open directory: " << folderPath << endl;
        return vector<string>();
    }

    vector<string> fileList;

    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            continue; // Bỏ qua thư mục
        }
        else {
            string fileName(findData.cFileName);
            if (fileName.find("_data.txt") == string::npos) {
                fileList.push_back(fileName); // Thêm tên tệp tin vào danh sách
            }
        }
    } while (FindNextFileA(hFind, &findData) != 0);

    FindClose(hFind);

    return fileList;
}
