#ifndef SOCIALAPP_H
#define SOCIALAPP_H

#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
using namespace std;

class User;
class Page;
class Post;
class Activity;
class Memory;
class Comment;
class Date;

class Activity {
public:
    Activity(const string& type, const string& value);
    string getType() const;
    string getValue() const;
    void displayActivtiy() const;

private:
    string type;
    string value;
};

class Comment{
public:
    Comment(const string& text, User* author);
    string getText() const;
    User* getAuthor() const;

private:
    string text;
    User* author;
};

class Date {
public:
    Date(int day, int month, int year);
    string toString() const;
    bool isValid() const;
    bool withinLastDay(const Date& currentDate) const;
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

private:
    int day;
    int month;
    int year;
};

class Post {
public:
    Post(string postID, const string& description, const Date& sharedDate);
    Post(string postID, const string& description, const Date& sharedDate, const Activity& sharedActivity);
    void addLike(User* user);
    void addComment(Comment* comment);
    Activity getActivity() const;
    string getPostID() const;
    string getDescription() const;
    int getLikes() const;
    Date getSharedDate() const;
    User** getLikedBy() const;
    Comment** getComments() const;
    int getNumComments() const;
    bool isLikedBy(User* user);
    virtual ~Post();

private:
    string postID;
    string description;
    Date sharedDate;
    Activity shareActivity;
    User** likedBy;
    Comment** comments;
    int numLikes;
    int numComments;
};

class Memory : public Post {
public:
    Memory(string postID, const string& memoryDescription, const Date& sharedDate, Post* originalPost);
    Post* getOriginalPost() const;
    string getMemoryDescription() const;

private:
    Post* originalPost;
    string memoryDescription;
};

class User {
public:
    User(const string& userID, const string& name);
    void addToFriendList(User* user);
    void addToLikedPages(Page* page);
    void addToTimeline(Post* post);
    string getUserID() const;
    string getName() const;
    User** getFriendList() const;
    Page** getLikedPages() const;
    Post** getTimeline() const;
    int getNumFriends() const; 
    int getNumLikedPages() const;
    int getNumPosts() const;
    void setUserID(string frend);
    ~User();

private:
    string userID;
    string name;
    User** friendList;
    Page** likedPages;
    Post** timeline;
    int numFriends = 0;
    int numLikedPages = 0 ;
    int numPosts = 0;
};

class Page {
public:
    Page(const string& pageID, const string& title, User* owner);
    ~Page();
    void addToTimeline(Post* post);
    string getPageID() const;
    string getTitle() const;
    User* getOwner() const;
    Post** getTimeline() const;
    int getNumPosts() const;
    void setPageID(string likedPage);
    Post* findPost(const string& postID);

private:
    string pageID;
    string title;
    User* owner;
    Post** timeline;
    int totalLikes;
    int numPosts;
};

class SocialNetworkApp {
public:
    SocialNetworkApp();
    ~SocialNetworkApp();
    void Run();
    void readDataFromFile(const string& filename);

private:
    User* currentUser;
    User** userList;
    Page** pageList;
    int numUsers;
    int numPages;
    Date currentDate;
    int memoryCounter;

    void setCurrentDate(Date initialDate);
    void setCurrentUser(const string& userID);
    void displayLikedPages();
    void displayHome();
    void displayUserTimeline();
    void displayPost(const Post& post);
    void viewFriendList();
    void viewPage(const string& pageID);
    void viewLikedUsers(const string& postID);
    void likePost(const string& id, const string& postID);
    void commentOnPost(const string& userID, const string& postID, const string& commentText);
    void seeYourMemories();
    void shareMemory(const string& postID, const string& text);
    void likePagePost(const string& pageID, const string& postID, User* user);
    void addPost(const string& description, const string& activityType, const string& activityValue);
    void addUser(const string& userID, const string& name);
};
#endif // !SOCIAL_APP_H
