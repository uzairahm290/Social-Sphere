#include "SocialApp.h"
#include <cstdlib> // For system()

void StylingPrint(const string hello) {
    cout << "\n";
    for (int i = 0; i < 120; i++) {
        cout << "_";
    }
    cout << "\n\n";
    cout << "\t\t\t\t\t\t\033[1m" << hello << "\033[0m\n";
    for (int i = 0; i < 120; i++) {
        cout << "_";
    }
    cout << endl << endl;
}
void PostSeparator() {
    cout << "\n\n";
    for (int i = 0; i < 30; i++) {
        cout << " ";
    }
    for (int i = 0; i < 60; i++) {
        cout << "*";
    }
    for (int i = 0; i < 30; i++) {
        cout << " ";
    }
    cout << "\n\n";
}
void StylingPrint2(const string hello) {
    cout << "\n";
    for (int i = 0; i < 30; i++) {
        cout << " ";
    }
    for (int i = 0; i < 60; i++) {
        cout << "*";
    }
    for (int i = 0; i < 30; i++) {
        cout << " ";
    }
    cout << "\n\n";
    cout << "\t\t\t\t\t\t\033[1m" << hello << "\033[0m\n\n";
    for (int i = 0; i < 30; i++) {
        cout << " ";
    }
    for (int i = 0; i < 60; i++) {
        cout << "*";
    }
    for (int i = 0; i < 30; i++) {
        cout << " ";
    }
    cout << endl << endl;
}
void logo() {
        cout << "\n\t\t\t _____ _____ _____ _____ _____ __           _____ _____ _____ _____ _____ _____\n"
            "\t\t\t|   __|     |     |     |  _  |  |         |   __|  _  |  |  |   __| __  |   __|\n"
            "\t\t\t|__   |  |  |   --|-   -|     |  |__       |__   |   __|     |   __|    -|   __|\n"
            "\t\t\t|_____|_____|_____|_____|__|__|_____|      |_____|__|  |__|__|_____|__|__|_____|\n\n" << endl;

}

Activity::Activity(const string& type = "", const string& value = "") : type(type), value(value) {}

string Activity::getType() const {          // type getter
    return type;
}

string Activity::getValue() const {         // value getter
    return value;
}

void Activity::displayActivtiy() const {
    cout << " is " << type << " " << value;
}

Date::Date(int day = 5, int month = 5, int year = 2024) : day(day), month(month), year(year) {}     // date constructor 

bool Date::isValid() const {
    if (year < 2000 || year > 2050) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1 || day > 31) {
        return false;
    }

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false; // April, June, September, November have 30 days
    }
    else if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            // Leap year
            if (day > 29) {
                return false;
            }
        }
        else {
            // Not a leap year
            if (day > 28) {
                return false;
            }
        }
    }

    return true;
}

bool Date::withinLastDay(const Date& currentDate) const {
    int daysDifference = currentDate.getDay() - day;
    int monthsDifference = currentDate.getMonth() - month;
    int yearsDifference = currentDate.getYear() - year;

    int totalDaysDifference = daysDifference + monthsDifference * 30 + yearsDifference * 365;

    return (totalDaysDifference >= 0 && totalDaysDifference <= 1);
}

string Date::toString() const {
    stringstream ss;
    ss << day << "/" << month << "/" << year;
    return ss.str();
}

Comment::Comment(const string& text, User* author) : text(text), author(author) {}          // Comment Constructor 

string Comment::getText() const {
    return text;
}

User* Comment::getAuthor() const {
    return author;
}

Post::Post(string postID, const string& description, const Date& sharedDate, const Activity& sharedActivity)
    : postID(postID), description(description), sharedDate(sharedDate), shareActivity(sharedActivity), numLikes(0), numComments(0) {
    likedBy = new User * [10];

    for (int i = 0; i < 10; i++) {
        likedBy[i] = nullptr;
    }

    comments = new Comment * [10];
    for (int i = 0; i < 10; i++) {
        comments[i] = nullptr;
    }
}

Post::Post(string postID, const string& description, const Date& sharedDate)
    : postID(postID), description(description), sharedDate(sharedDate), numLikes(0), numComments(0) {
    likedBy = new User * [10];

    for (int i = 0; i < 10; i++) {
        likedBy[i] = nullptr;
    }

    comments = new Comment * [10];
    for (int i = 0; i < 10; i++) {
        comments[i] = nullptr;
    }
}

void Post::addLike(User* user) {
    User** newLikedBy = new User * [numLikes + 1];

    for (int i = 0; i < numLikes; i++) {
        newLikedBy[i] = likedBy[i];
    }

    newLikedBy[numLikes] = user;

    delete[] likedBy;

    likedBy = newLikedBy;

    ++numLikes;
}

void Post::addComment(Comment* comment) {

    Comment** newComments = new Comment * [numComments + 1];

    for (int i = 0; i < numComments; i++) {
        newComments[i] = comments[i];
    }

    newComments[numComments] = comment;

    delete[] comments;

    comments = newComments;

    ++numComments;
}

string Post::getPostID() const {
    return postID;
}

string Post::getDescription() const {
    return description;
}

int Post::getLikes() const {
    return numLikes;
}

int Post::getNumComments() const {
    return numComments;
}

int Page::getNumPosts() const {
    return numPosts;
}

Date Post::getSharedDate() const {
    return sharedDate;
}

User** Post::getLikedBy() const {
    return likedBy;
}

Comment** Post::getComments() const {
    return comments;
}

Memory::Memory(string postID, const string& memoryDescription, const Date& sharedDate, Post* originalPost)
    : Post(postID, "Memory", sharedDate), memoryDescription(memoryDescription), originalPost(originalPost) {}


Post* Memory::getOriginalPost() const {
    return originalPost;
}


string Memory::getMemoryDescription() const {
    return memoryDescription;
}


User::User(const string& userID = 0, const string& name = 0)
    : userID(userID), name(name), numFriends(0), numLikedPages(0), numPosts(0) {
    friendList = new User * [10]; 
    for (int i = 0; i < 10; i++) {
        friendList[i] = nullptr;
    }
    likedPages = new Page * [10]; 
    for (int i = 0; i < 10; i++) {
        likedPages[i] = nullptr;
    }
    timeline = new Post * [10];
    for (int i = 0; i < 10; i++) {
        timeline[i] = nullptr;
    }
}

void User::addToFriendList(User* user) {
    User** newFriendList = new User * [numFriends + 1];

    for (int i = 0; i < numFriends; i++) {
        newFriendList[i] = friendList[i];
    }

    newFriendList[numFriends] = user;

    delete[] friendList;

    friendList = newFriendList;

    ++numFriends;
}

void User::addToLikedPages(Page* page) {
    Page** newLikedPages = new Page * [numLikedPages + 1];

    for (int i = 0; i < numLikedPages; i++) {
        newLikedPages[i] = likedPages[i];
    }

    newLikedPages[numLikedPages] = page;

    delete[] likedPages;

    likedPages = newLikedPages;

    ++numLikedPages;
}

Activity Post::getActivity() const {
    return shareActivity;
}

bool Post::isLikedBy(User* user) {
    for (int i = 0; i < numLikes; i++) {
        if (likedBy[i] == user) {
            return true;
        }
    }
    return false;
}

int User::getNumFriends() const {
    return numFriends;
}

void User::setUserID(string frend) {
    userID = frend;
}

int User::getNumLikedPages() const {
    return numLikedPages;
}

int User::getNumPosts() const {
    return numPosts;
}

void User::addToTimeline(Post* post) {
    Post** newTimeline = new Post * [numPosts + 1];

    for (int i = 0; i < numPosts; i++) {
        newTimeline[i] = timeline[i];
    }

    newTimeline[numPosts] = post;

    delete[] timeline;

    timeline = newTimeline;

    ++numPosts;
}


User::~User() {
    for (int i = 0; i < numFriends; i++) {
        delete friendList[i];
    }
    delete[] friendList;

    for (int i = 0; i < numLikedPages; i++) {
        delete likedPages[i];
    }
    delete[] likedPages;

    for (int i = 0; i < numPosts; i++) {
        delete timeline[i];
    }
    delete[] timeline;
}

Page::~Page() {
    for (int i = 0; i < numPosts; i++) {
        delete timeline[i];
    }
    delete[] timeline;
}

Post::~Post() {

    if (likedBy != nullptr) {
        delete[] likedBy;
    }
    if (comments != nullptr) {
        delete[] comments;
    }
}

Post* Page::findPost(const string& postID) {
    for (int i = 0; i < numPosts; i++) {
        if (timeline[i]->getPostID() == postID) {
            return timeline[i];
        }
    }
    return nullptr;
}

string User::getUserID() const {
    return userID;
}

string User::getName() const {
    return name;
}

User** User::getFriendList() const {
    return friendList;
}

Page** User::getLikedPages() const {
    return likedPages;
}

Post** User::getTimeline() const {
    return timeline;
}

Page::Page(const string& pageID, const string& title, User* owner)
    : pageID(pageID), title(title), owner(owner), totalLikes(0), numPosts(0) {
    timeline = new Post * [10];  // Allocate memory for timeline
}

void Page::addToTimeline(Post* post) {
    Post** newTimeline = new Post * [numPosts + 1];

    for (int i = 0; i < numPosts; i++) {
        newTimeline[i] = timeline[i];
    }

    newTimeline[numPosts] = post;

    delete[] timeline;

    timeline = newTimeline;

    ++numPosts;
}

string Page::getPageID() const {
    return pageID;
}

void Page::setPageID(string likedPage) {
    pageID = likedPage;
}

string Page::getTitle() const {
    return title;
}

User* Page::getOwner() const {
    return owner;
}

Post** Page::getTimeline() const {
    return timeline;
}

SocialNetworkApp::SocialNetworkApp() : currentUser(nullptr), userList(nullptr), pageList(nullptr), numUsers(0), numPages(0), memoryCounter(0) {}

SocialNetworkApp::~SocialNetworkApp() {
    if (userList != nullptr) {
        for (int i = 0; i < numUsers; i++) {
            delete userList[i];
        }
        delete[] userList;
    }

    if (pageList != nullptr) {
        for (int i = 0; i < numPages; i++) {
            delete pageList[i];
        }
        delete[] pageList;
    }

    if (currentUser != nullptr) {
        delete currentUser;
    }
}

void SocialNetworkApp::Run() {
    logo();
    while (1) {
        int initialDay, initialMonth, initialYear;
        cout << "Enter the initial date (day month year): ";
        cin >> initialDay >> initialMonth >> initialYear;
        Date initialDate(initialDay, initialMonth, initialYear);
        if (initialDate.isValid()) {
            setCurrentDate(initialDate);
            break;
        }
        else {
            cout << "Invalid Date Enter Again!!!!!!" << endl;
        }
    }
    string initialUserID;
    while (1) {
        cout << "\n\nEnter your user ID to log in: ";
        cin >> initialUserID;
        if (currentUser == nullptr) {
            setCurrentUser(initialUserID);
            if (currentUser != nullptr) {
                break;
            }
        }
    }

    while (true) {
        logo();
        cout << "\t\t\t\t\t\t=============================" << endl;
        cout << "\t\t\t\t\t\t===========  Menu =========== " << endl;
        cout << "\t\t\t\t\t\t=============================" << endl << endl;
        cout << "\t\t1. View Home" << endl;
        cout << "\t\t2. View Friend List" << endl;
        cout << "\t\t3. View Liked Pages" << endl;
        cout << "\t\t4. View User Timeline" << endl;
        cout << "\t\t5. Search Post" << endl;
        cout << "\t\t6. View Users Who Liked Post" << endl;
        cout << "\t\t7. Search Page" << endl;
        cout << "\t\t8. Like Post" << endl;
        cout << "\t\t9. Comment On Post" << endl;
        cout << "\t\t10. View Memories" << endl;
        cout << "\t\t11. Share Memory" << endl;
        cout << "\t\t12. Add a Post" << endl;
        cout << "\t\t13. Change Current User" << endl;
        cout << "\t\t14. Available Users" << endl;
        cout << "\t\t15. Add New User" << endl;
        cout << "\t\t16. Logout" << endl;
        cout << "=============================" << endl;
        cout << "=====  Choose an option ====="<< endl;
        cout << "=============================" << endl;


        int option;
        cin >> option;

        string inputData;
        switch (option) {
        case 1:
            system("cls");
            logo();
            cout << "\t\t\t\t\t\t  _  _               \n"
                "\t\t\t\t\t\t | || |___ _ __  ___ \n"
                "\t\t\t\t\t\t | __ / _ \\ '  \\/ -_)\n"
                "\t\t\t\t\t\t |_||_\\___/_|_|_\\___|\n\n";
            displayHome();
            break;
        case 2:
            system("cls");
            cout << "\t\t\t\t\t   ___    _             _      _    _    _   \n"
                "\t\t\t\t\t  | __| _(_)___ _ _  __| |___ | |  (_)__| |_ \n"
                "\t\t\t\t\t  | _| '_| / -_) ' \\/ _` (_-< | |__| (_-< _| \n"
                "\t\t\t\t\t  |_||_| |_\\___|_||_\\__,_/__/ |____|_/__|\\__|\n"
                "\t\t\t\t\t                                             \n"; 
            viewFriendList();
            break;
        case 3:
            system("cls");
            cout << "\t\t\t\t\t\t   _    _ _          _   ___                  \n"
                "\t\t\t\t\t\t  | |  (_) |_____ __| | | _ \\__ _ __ _ ___ ___\n"
                "\t\t\t\t\t\t  | |__| | / / -_) _` | |  _/ _` / _` / -_|_-<\n"
                "\t\t\t\t\t\t  |____|_|_\\_\\___\\__,_| |_| \\__,_\\__, \\___/__/\n"
                "\t\t\t\t\t\t                                 |___/        \n";
            displayLikedPages();
            break;
        case 4:
            system("cls");
            cout << "\t\t\t\t\t  _____ _           _ _          \n"
                << "\t\t\t\t\t |_   _(_)_ __  ___| (_)_ _  ___ \n"
                << "\t\t\t\t\t   | | | | '  \\/ -_) | | ' \\/ -_)\n"
                << "\t\t\t\t\t   |_| |_|_|_|\\___|_|_|_||_\\___|\n"
                << "\t\t\t\t\t                                 \n";
            displayUserTimeline();
            break;
        case 5: {
            system("cls");
            cout << "\t\t\t\t\t  ___                  _      ___        _   \n"
                << "\t\t\t\t\t / __| ___ __ _ _ _ __| |_   | _ \\___ __| |_ \n"
                << "\t\t\t\t\t \\__ \\/ -_) _` | '_/ _| ' \\  |  _/ _ (_-<  _|\n"
                << "\t\t\t\t\t |___/\\___\\__,_|_| \\__|_||_| |_| \\___/__\\__|\n\n\n";
            string postID;
            cout << "Enter the post ID: ";
            cin >> postID;
            bool found = false;
            Post** timeline = currentUser->getTimeline();
            for (int i = 0; i < currentUser->getNumPosts(); i++) {
                if (timeline[i]->getPostID() == postID) {
                    PostSeparator();
                    displayPost(*timeline[i]);
                    PostSeparator();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Post with ID " << postID << " not found." << endl;
            }
            break;
        }
        case 6: {
            system("cls");
            cout << "\t\t\t\t\t  _    _ _           \n"
                << "\t\t\t\t\t | |  (_) |_____ ___ \n"
                << "\t\t\t\t\t | |__| | / / -_|_-< \n"
                << "\t\t\t\t\t |____|_|_\\_\\___/__/ \n";

            string postID;
            cout << "Enter the post ID: ";
            cin >> postID;
            viewLikedUsers(postID);
            break;
        }
        case 7: {
            system("cls");
            cout << "\t\t\t\t\t  ___               \n"
                << "\t\t\t\t\t | _ \\__ _ __ _ ___ \n"
                << "\t\t\t\t\t |  _/ _` / _` / -_)\n"
                << "\t\t\t\t\t |_| \\__,_\\__, \\___|\n"
                << "\t\t\t\t\t          |___/     \n\n";
            string pageID;
            cout << "Enter the page ID: ";
            cin >> pageID;
            viewPage(pageID);
            char yourChoice;
            cout << "Do you want to like a post on this Page (y/n)\t";
            cin >> yourChoice;
            if (yourChoice == 'y') {
                string postID;
                cout << "Enter the post ID: ";
                cin >> postID;
                likePagePost(pageID, postID, currentUser);
                break;
            }
            else {
                break;
            }
        }
        case 8: {
            system("cls");
            cout << "\t\t\t\t\t  _    _ _         ___        _   \n"
                << "\t\t\t\t\t | |  (_) |_____  | _ \\___ __| |_ \n"
                << "\t\t\t\t\t | |__| | / / -_) |  _/ _ (_-<  _|\n"
                << "\t\t\t\t\t |____|_|_\\_\\___| |_| \\___/__\\__|\n";
            string id, postID;
            cout << "Enter the user ID or page ID: ";
            cin >> id;
            cout << "Enter the post ID: ";
            cin >> postID;
            likePost(id, postID);
            break;
        }
        case 9: {
            system("cls");
            cout << "\t\t\t\t\t    _      _    _    ___                         _    \n"
                << "\t\t\t\t\t   /_\\  __| |__| |  / __|___ _ __  _ __  ___ _ _| |_  \n"
                << "\t\t\t\t\t  / _ \\/ _` / _` | | (__/ _ \\ '  \\| '  \\/ -_) ' \\  _| \n"
                << "\t\t\t\t\t /_/ \\_\\__,_\\__,_|  \\___\\___/_|_|_|_|_|_\\___|_||_\\__| \n\n";
            string userID, postID, comment;
            cout << "Enter the user or Page ID: ";
            cin >> userID;
            cout << "Enter the post ID: ";
            cin >> postID;
            cout << "Enter your comment: ";
            cin.ignore();
            getline(cin, comment);
            commentOnPost(userID, postID, comment);
            break;
        }
        case 10:
            system("cls");
            cout << "\t\t\t\t\t  __  __                   _         \n"
                << "\t\t\t\t\t |  \\/  |___ _ __  ___ _ _(_)___ ___ \n"
                << "\t\t\t\t\t | |\\/| / -_) '  \\/ _ \\ '_| / -_|_-< \n"
                << "\t\t\t\t\t |_|  |_\\___|_|_|_\\___/_| |_\___/__/ \n";

            seeYourMemories();
            break;
        case 11: {
            system("cls");
            cout << "\t\t\t\t\t  ___ _                   __  __                        \n"
                << "\t\t\t\t\t / __| |_  __ _ _ _ ___  |  \\/  |___ _ __  ___ _ _ _  _ \n"
                << "\t\t\t\t\t \\__ \\ ' \\/ _` | '_/ -_) | |\\/| / -_) '  \\/ _ \\ '_| || |\n"
                << "\t\t\t\t\t |___/_||_\\__,_|_| \\___| |_|  |_\\___|_|_|_\\___/_|  \\_, |\n"
                << "\t\t\t\t\t                                                   |__/ \n\n\n";
            string postID, memory;
            cout << "Enter the post ID: ";
            cin >> postID;
            cout << "Enter the memory to share: ";
            cin.ignore();
            getline(cin, memory);
            shareMemory(postID, memory);
            break;
        }
        case 12:
            system("cls");
            cout << "\t\t\t\t\t    _      _    _   ___        _   \n"
                << "\t\t\t\t\t   /_\\  __| |__| | | _ \\___ __| |_ \n"
                << "\t\t\t\t\t  / _ \\/ _` / _` | |  _/ _ (_-<  _|\n"
                << "\t\t\t\t\t /_/ \\_\\__,_\\__,_| |_| \\___/__\\__|\n\n\n";
            cout << "Enter the Post Text : ";
            cin.ignore();
            getline(cin, inputData);
            char yourChoice;
            cout << "\nDo you want to add activity (y/n)\t";
            cin >> yourChoice;
            if (yourChoice == 'y') {
                string value, type;
                cout << "\nEnter Activity type :";
                cin.ignore();
                getline(cin, type);
                cout << "\nEnter Activity value :";
                cin.ignore();
                getline(cin, value);
                addPost(inputData, type, value);
                break;
            }
            else {
                addPost(inputData, "", "");
                break;
            }
        case 13:
            system("cls");
            cout << "\t\t\t\t\t  ___        _ _      _      _   _              \n"
                << "\t\t\t\t\t / __|_ __ _(_) |_ __| |_   | | | |___ ___ _ _  \n"
                << "\t\t\t\t\t \\__ \\ V  V / |  _/ _| ' \\  | |_| (_-</ -_) '_| \n"
                << "\t\t\t\t\t |___/\\_/\\_/|_|\\__\\__|_||_|  \\___//__/\\___|_|   \n"
                << "\t\t\t\t\t                                                \n\n\n";
            currentUser = nullptr;
            while (1) {
                cout << "Enter your user ID to log in: ";
                cin >> initialUserID;
                if (currentUser == nullptr) {
                    setCurrentUser(initialUserID);
                    if (currentUser != nullptr) {
                        break;
                    }
                }
            }
            break;
        case 14:
            system("cls");
            cout << "\t\t\t\t\t  _   _                 \n"
                << "\t\t\t\t\t | | | |___ ___ _ _ ___ \n"
                << "\t\t\t\t\t | |_| (_-</ -_) '_(_-< \n"
                << "\t\t\t\t\t  \\___//__/\\___|_| /__/ \n"
                << "\t\t\t\t\t                        \n";
            for (int i = 0; i < numUsers; i++) {
                cout << "\t\t\tUser ID: " << userList[i]->getUserID() << "\t Name: " << userList[i]->getName() << endl;
            }
            break;
        case 15:
        {
            system("cls");
            cout << "\t\t\t\t\t  ___ _             _   _        \n"
                << "\t\t\t\t\t / __(_)__ _ _ _   | | | |_ __   \n"
                << "\t\t\t\t\t \\__ \\ / _` | ' \\  | |_| | '_ \\  \n"
                << "\t\t\t\t\t |___/_\\__, |_|_|_|  \\___/| .__/  \n"
                << "\t\t\t\t\t       |___/             |_|     \n";
            string userID, name;
            bool userExists;

            do {
                userExists = false; 
                cout << "Enter User ID: ";
                cin >> userID;
                cin.ignore(); 

                for (int i = 0; i < numUsers; i++) {
                    if (userList[i]->getUserID() == userID) {
                        cout << "Error: UserID " << userID << " already exists." << endl;
                        userExists = true;
                        break;
                    }
                }
            } while (userExists);

            cout << "Enter Name: ";
            getline(cin, name);

            addUser(userID, name);
            break;
        }
        case 16:
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\t\t";
            cout << " ___________ ___ ___     _____    _______    ____  __.    _____.___.________    ____ ___  \n\t\t";
            cout << " \\__    ___//   |   \\   /  _  \\   \\      \\  |    |/ _|    \\__  |   |\\_____  \\  |    |   \\ \n\t\t";
            cout << "   |    |  /    ~    \\ /  /_\\  \\  /   |   \\ |      <       /   |   | /   |   \\ |    |   / \n\t\t";
            cout << "   |    |  \\    Y    //    |    \\/    |    \\|    |  \\      \\____   |/    |    \\|    |  /  \n\t\t";
            cout << "   |____|   \\___|_  / \\____|__  /\\____|__  /|____|__ \\     / ______|\\_______  /|______/   \n\t\t";
            cout << "                 \\/          \\/         \\/         \\/     \\/               \\/            \n\n\n\n\n\n\n\n\n\n";
            exit(0);
        default:
            cout << "Invalid option. Please try again." << endl;
        }
        char userChoice;
        cout << "\nPress 'M' to show menu again, or any other key to Exit: ";
        cin >> userChoice;
        if (userChoice != 'M' && userChoice != 'm') {
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\t\t";
            cout << " ___________ ___ ___     _____    _______    ____  __.    _____.___.________    ____ ___  \n\t\t";
            cout << " \\__    ___//   |   \\   /  _  \\   \\      \\  |    |/ _|    \\__  |   |\\_____  \\  |    |   \\ \n\t\t";
            cout << "   |    |  /    ~    \\ /  /_\\  \\  /   |   \\ |      <       /   |   | /   |   \\ |    |   / \n\t\t";
            cout << "   |    |  \\    Y    //    |    \\/    |    \\|    |  \\      \\____   |/    |    \\|    |  /  \n\t\t";
            cout << "   |____|   \\___|_  / \\____|__  /\\____|__  /|____|__ \\     / ______|\\_______  /|______/   \n\t\t";
            cout << "                 \\/          \\/         \\/         \\/     \\/               \\/            \n\n\n\n\n\n\n\n\n\n";
            exit(0);
        }
    }
}

void SocialNetworkApp::readDataFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    if (!file.is_open()) {
        cout << "Error Opening File" << endl;
        return;
    }

    int maxUsers = 10;
    userList = new User * [maxUsers];
    for (int i = 0; i < maxUsers; i++) {
        userList[i] = nullptr;
    }

    int maxPages = 10;
    pageList = new Page * [maxPages];
    for (int i = 0; i < maxPages; i++) {
        pageList[i] = nullptr;
    }

    int numFriends = 0, numLPages = 0, numPosts = 0;

    while (getline(file, line)) {
        if (line == "USER") {
            break;
        }
    }
    int userCount = 0;
    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        stringstream ss(line);
        string userID, userName, token;
        getline(ss, userID, ',');
        getline(ss, userName, ',');
        ss >> numFriends >> numLPages >> numPosts;
        userList[userCount] = new User(userID, userName);
        userCount++;
    }
    numUsers = userCount;

    while (getline(file, line)) {
        if (line == "PAGE") {
            break;
        }
    }
    int pageCount = 0;
    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        stringstream ss(line);
        string pageID, pageName, OwnerID;
        getline(ss, pageID, ',');
        getline(ss, pageName, ',');
        getline(ss, OwnerID, ',');
        string ownerName;
        for (int i = 0; i < numUsers; i++) {
            if (userList[i]->getUserID() == OwnerID) {
                ownerName = userList[i]->getName();
                break;
            }
        }
        User* Owner = new User(OwnerID, ownerName);
        pageList[pageCount] = new Page(pageID, pageName, Owner);
        pageCount++;
    }
    numPages = pageCount;

    while (getline(file, line)) {
        if (line == "USER_FRIENDS") {
            break;
        }
    }
    userCount = 0;
    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        stringstream ss(line);
        string friendID;
        for (int i = 0; i < numFriends; i++) {
            getline(ss, friendID, ',');
            string friendName;
            for (int j = 0; j < numUsers; j++) {
                if (userList[j]->getUserID() == friendID) {
                    friendName = userList[j]->getName();
                    break;
                }
            }
            User* friendUser = new User(friendID, friendName); // Create new User instance
            userList[userCount]->addToFriendList(friendUser);
        }
        userCount++;
    }

    while (getline(file, line)) {
        if (line == "LIKED_PAGES") {
            break;
        }
    }
    userCount = 0;
    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        stringstream ss(line);
        string pageID;
        for (int i = 0; i < numLPages; i++) {
            getline(ss, pageID, ',');
            Page* likedPage = nullptr;
            for (int j = 0; j < numPages; j++) {
                if (pageList[j]->getPageID() == pageID) {
                    likedPage = pageList[j];
                    break;
                }
            }
            if (likedPage != nullptr) {
                userList[userCount]->addToLikedPages(likedPage);
            }
        }
        userCount++;
    }

    while (getline(file, line)) {
        if (line == "POST") {
            break;
        }
    }
    userCount = 0;
    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        string userID, postID, postDisc, token, likedby;
        int day, month, year, nPostLikes;
        stringstream ss(line);
        getline(ss, userID, ',');
        getline(ss, postID, ',');
        getline(ss, postDisc, ',');
        ss >> day >> month >> year >> nPostLikes;
        Date uploadDate(day, month, year);
        Post* uploadPost = new Post(postID, postDisc, uploadDate);
        for (int i = 0; i < nPostLikes; i++) {
            getline(ss, likedby, ',');
            for (int j = 0; j < numUsers; j++) {
                if (userList[j]->getUserID() == likedby) {
                    uploadPost->addLike(userList[j]);
                }
            }
        }
        for (int i = 0; i < numUsers; i++) {
            if (userList[i]->getUserID() == userID) {
                userList[i]->addToTimeline(uploadPost);
            }
        }
    }

    // Adding Acitvities
    Date newdate(5, 5, 2024);
    Activity newAcivity("Celebrating", "Birthday");
    Post* activityPost = new Post("post4", "Today is my Mother's Birthday", newdate, newAcivity);
    userList[1]->addToTimeline(activityPost);

    Date newdate1(4, 5, 2024);
    Activity newAcivity1("Feeling", "Excited");
    Post* activityPost1 = new Post("post4", "I am going for a ride on My Kawasaki Ninja H2R", newdate1, newAcivity1);
    userList[0]->addToTimeline(activityPost1);

    Date newdate2(3, 5, 2024);
    Activity newAcivity2("Thinking about", "Marriage");
    Post* activityPost2 = new Post("post4", "During an event of my cousins marriage", newdate2, newAcivity2);
    userList[2]->addToTimeline(activityPost2);

    Date newdate3(2, 5, 2024);
    Activity newAcivity3("Making", "Money");
    Post* activityPost3 = new Post("post4", "I am working on a freelance Website", newdate3, newAcivity3);
    userList[3]->addToTimeline(activityPost3);

    while (getline(file, line)) {
        if (line == "PAGE_POST") {
            break;
        }
    }
    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        string pageID, postID, postDisc, likedby;
        int day, month, year, nPostLikes;
        stringstream ss(line);
        getline(ss, pageID, ',');
        getline(ss, postID, ',');
        getline(ss, postDisc, ',');
        ss >> day >> month >> year >> nPostLikes;
        Date uploadDate(day, month, year);
        Post* uploadPost = new Post(postID, postDisc, uploadDate);
        for (int i = 0; i < nPostLikes; i++) {
            getline(ss, likedby, ',');
            for (int j = 0; j < numUsers; j++) {
                if (userList[j]->getUserID() == likedby) {
                    uploadPost->addLike(userList[j]);
                }
            }
        }
        for (int i = 0; i < numPages; i++) {
            if (pageList[i]->getPageID() == pageID) {
                pageList[i]->addToTimeline(uploadPost);
            }
        }

    }

    while (getline(file, line)) {
        if (line == "PAGE_COMMENT") {
            break;
        }
    }
    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        string pageID, postID, commenterID, commentDesc;
        stringstream ss(line);
        getline(ss, pageID, ',');
        getline(ss, postID, ',');
        getline(ss, commenterID, ',');
        getline(ss, commentDesc, ',');

        User* commenter = nullptr;
        for (int j = 0; j < numUsers; j++) {
            if (userList[j]->getUserID() == commenterID) {
                commenter = userList[j];
                break;
            }
        }

        Comment* postComment = new Comment(commentDesc, commenter);

        for (int i = 0; i < numUsers; i++) {
            if (pageList[i]->getPageID() == pageID) {
                for (int j = 0; j < pageList[i]->getNumPosts(); j++) {
                    if (pageList[i]->getTimeline()[j]->getPostID() == postID) {
                        pageList[i]->getTimeline()[j]->addComment(postComment);
                        break;
                    }
                }
                break;
            }
        }
    }

    while (getline(file, line)) {
        if (line == "COMMENT") {
            break;
        }
    }

    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        string userID, postID, commenterID, commentDesc;
        stringstream ss(line);
        getline(ss, postID, ',');
        getline(ss, userID, ',');
        getline(ss, commenterID, ',');
        getline(ss, commentDesc, ',');

        User* commenter = nullptr;
        for (int j = 0; j < numUsers; j++) {
            if (userList[j]->getUserID() == commenterID) {
                commenter = userList[j];
                break;
            }
        }

        Comment* postComment = new Comment(commentDesc, commenter);

        for (int i = 0; i < numUsers; i++) {
            if (userList[i]->getUserID() == userID) {
                for (int j = 0; j < userList[i]->getNumPosts(); j++) {
                    if (userList[i]->getTimeline()[j]->getPostID() == postID) {
                        userList[i]->getTimeline()[j]->addComment(postComment);
                        break;
                    }
                }
                break;
            }
        }
    }
    file.close();
}

void SocialNetworkApp::setCurrentDate(Date initialDate) {
    currentDate = initialDate;
}

void SocialNetworkApp::setCurrentUser(const string& userID) {
    for (int i = 0; i < numUsers; i++) {
        if (userList[i]->getUserID() == userID) {
            currentUser = userList[i];
            string decorator = "Welcome Back " + currentUser->getName();
            StylingPrint2(decorator);
            return;
        }
    }
    cout << "\nUser with ID " << userID << " not found.\n" << endl;
}

void SocialNetworkApp::displayLikedPages() {
    Page** likedPages = currentUser->getLikedPages();

    if (likedPages == nullptr || currentUser->getNumLikedPages() == 0) {
        cout << "You haven't liked any pages yet." << endl;
        return;
    }
    cout << endl;
    for (int i = 0; i < currentUser->getNumLikedPages(); i++) {
        Page* page = likedPages[i];
        cout << "\t\t\tYou liked Page \" " << page->getTitle() << " \" by " << page->getOwner()->getName() << endl;
        cout << endl;
    }
}

void SocialNetworkApp::displayHome() {
    Date currentDate = this->currentDate;
    StylingPrint2("Posts of friends shared in the last day:");
    User** friendList = currentUser->getFriendList();
    int numFriends = currentUser->getNumFriends();
    for (int i = 0; i < numFriends; i++) {
        string uID = friendList[i]->getUserID();
        for (int k = 0; k < numUsers; k++) {
            if (userList[k]->getUserID() == uID) {
                int numFPosts = userList[k]->getNumPosts();
                for (int j = 0; j < numFPosts; j++) {
                    if (userList[k]->getTimeline()[j]->getSharedDate().withinLastDay(currentDate)) {
                        cout << userList[k]->getName() << " shared a post ";
                        displayPost(*userList[k]->getTimeline()[j]);
                        PostSeparator();
                        break;
                    }
                }
                break;
            }
        }
    }
    StylingPrint2("Posts of liked pages shared in the last day");
    Page** likedPages = currentUser->getLikedPages();
    int numLikedPages = currentUser->getNumLikedPages();
    for (int i = 0; i < numLikedPages; i++) {
        Post** pageTimeline = likedPages[i]->getTimeline();
        int numPagePosts = likedPages[i]->getNumPosts();
        for (int j = 0; j < numPagePosts; j++) {
            if (pageTimeline[j]->getSharedDate().withinLastDay(currentDate)) {
                cout << likedPages[i]->getTitle() << " shared a post";
                displayPost(*pageTimeline[j]);
                PostSeparator();
                cout << endl;
            }
        }
    }
}

void SocialNetworkApp::displayUserTimeline() {
    if (currentUser == nullptr || currentUser->getNumPosts() == 0) {
        cout << "Your timeline is empty." << endl;
        return;
    }

    cout << endl;
    Post** timeline = currentUser->getTimeline();
    for (int i = 0; i < currentUser->getNumPosts(); i++) {
        cout << currentUser->getName() << " shared a post \n";
        displayPost(*timeline[i]);
        PostSeparator();
        cout << endl;
    }
}

void SocialNetworkApp::displayPost(const Post& post) {
    Activity activity = post.getActivity();
    if (!activity.getType().empty() && !activity.getValue().empty()) {
        cout << currentUser->getName();
        post.getActivity().displayActivtiy();
    }
    if (post.getPostID() != "memoryID") {
        cout << endl << endl;
        cout << post.getDescription() << "\t.......... ( " << post.getPostID() << "\t" << post.getSharedDate().toString() << " ) " << endl << endl;
        cout << "Likes: " << post.getLikes() << "\t\tTotal Comments:" << post.getNumComments() << endl;

        // Display comments
        Comment** comments = post.getComments();
        int numComments = post.getNumComments();
        if (numComments > 0) {
            cout << "Comments:" << endl;
            for (int i = 0; i < numComments; i++) {
                cout << comments[i]->getAuthor()->getName() << " Commented \n\t\t" << comments[i]->getText() << endl;
            }
        }
    }
    else {
        seeYourMemories();
    }

}

void SocialNetworkApp::viewFriendList() {
    User** friendList = currentUser->getFriendList();
    int numFriends = currentUser->getNumFriends();
    cout << "\n\n\n";
    for (int i = 0; i < numFriends; i++) {
        cout << "\t\t\t\t\t" << i + 1 << ". " << friendList[i]->getUserID() << "\t" << friendList[i]->getName() << endl;
    }
}

void SocialNetworkApp::viewPage(const string& pageID) {
    for (int i = 0; i < numPages; i++) {
        if (pageList[i]->getPageID() == pageID) {
            Page* page = pageList[i];
            cout << "Page ID: " << page->getPageID() << endl;
            cout << "Title: " << page->getTitle() << endl;
            cout << "Owner: " << page->getOwner()->getName() << endl;
            Post** timeline = page->getTimeline();
            int numPosts = page->getNumPosts();
            StylingPrint2("Posts on Page Timeline : ");
            for (int j = 0; j < numPosts; j++) {
                cout << page->getTitle() << " shared a post \n";
                displayPost(*timeline[j]);
                PostSeparator();
                cout << endl;
            }
            return;
        }
    }
    cout << "Page with ID " << pageID << " not found." << endl;
}

void SocialNetworkApp::viewLikedUsers(const string& postID) {
    Post** timeline = currentUser->getTimeline();
    int numPosts = currentUser->getNumPosts();
    for (int i = 0; i < numPosts; i++) {
        if (timeline[i]->getPostID() == postID) {
            StylingPrint2("Users who liked the post with ID");
            User** likedBy = timeline[i]->getLikedBy();
            int numLikes = timeline[i]->getLikes();
            for (int j = 0; j < numLikes; j++) {
                cout << "\t\t\t" << likedBy[j]->getName() << " liked your Post." << endl;
            }
            return;
        }
    }
    cout << "Post with ID " << postID << " not found." << endl;
}

void SocialNetworkApp::likePost(const string& id, const string& postID) {
    User* user = nullptr;
    Page* page = nullptr;

    for (int i = 0; i < numUsers; i++) {
        if (userList[i]->getUserID() == id) {
            user = userList[i];
            break;
        }
    }

    if (!user) {
        for (int i = 0; i < numPages; i++) {
            if (pageList[i]->getPageID() == id) {
                page = pageList[i];
                break;
            }
        }
    }

    if (!user && !page) {
        cout << "User or page with ID " << id << " not found." << endl;
        return;
    }

    if (user) {
        Post** userTimeline = user->getTimeline();
        int numUserPosts = user->getNumPosts();
        for (int i = 0; i < numUserPosts; i++) {
            if (userTimeline[i]->getPostID() == postID) {
                userTimeline[i]->addLike(currentUser);
                cout << "You liked the post with ID " << postID << " from user " << user->getName() << "." << endl;
                return;
            }
        }
        cout << "Post with ID " << postID << " not found on user's timeline." << endl;
        return;
    }

    if (page) {
        Post** pageTimeline = page->getTimeline();
        int numPagePosts = page->getNumPosts();
        for (int i = 0; i < numPagePosts; i++) {
            if (pageTimeline[i]->getPostID() == postID) {
                pageTimeline[i]->addLike(currentUser);
                cout << "You liked the post with ID " << postID << " from page " << page->getTitle() << "." << endl;
                return;
            }
        }
        cout << "Post with ID " << postID << " not found on page's timeline." << endl;
        return;
    }
}

void SocialNetworkApp::commentOnPost(const string& id, const string& postID, const string& commentText) {
    User* user = nullptr;
    Page* page = nullptr;

    for (int i = 0; i < numUsers; i++) {
        if (userList[i]->getUserID() == id) {
            user = userList[i];
            break;
        }
    }

    if (!user) {
        for (int i = 0; i < numPages; i++) {
            if (pageList[i]->getPageID() == id) {
                page = pageList[i];
                break;
            }
        }
    }

    if (!user && !page) {
        cout << "User or page with ID " << id << " not found." << endl;
        return;
    }

    if (user) {
        Post** userTimeline = user->getTimeline();
        int numUserPosts = user->getNumPosts();
        for (int i = 0; i < numUserPosts; i++) {
            if (userTimeline[i]->getPostID() == postID) {
                Comment* comment = new Comment(commentText, currentUser);
                userTimeline[i]->addComment(comment);
                cout << "Comment added to the post with ID " << postID << " on user's timeline." << endl;
                return;
            }
        }
        cout << "Post with ID " << postID << " not found on user's timeline." << endl;
        return;
    }

    if (page) {
        Post** pageTimeline = page->getTimeline();
        int numPagePosts = page->getNumPosts();
        for (int i = 0; i < numPagePosts; i++) {
            if (pageTimeline[i]->getPostID() == postID) {
                Comment* comment = new Comment(commentText, currentUser);
                pageTimeline[i]->addComment(comment);
                cout << "Comment added to the post with ID " << postID << " on page's timeline." << endl;
                return;
            }
        }
        cout << "Post with ID " << postID << " not found on page's timeline." << endl;
        return;
    }
}

void SocialNetworkApp::seeYourMemories() {
    Post** timeline = currentUser->getTimeline();
    int numPosts = currentUser->getNumPosts();

    int currentDay = currentDate.getDay();
    int currentMonth = currentDate.getMonth();
    int currentYear = currentDate.getYear();
    bool foundMemory = false; 
    for (int i = 0; i < numPosts; i++) {
        Post* post = timeline[i];
        Date postDate = post->getSharedDate();
        int yearsElapsed = 0;
        if (postDate.getDay() == currentDay && postDate.getMonth() == currentMonth) {
            if (dynamic_cast<Memory*>(post) != nullptr) {
                foundMemory = true; 
                yearsElapsed = currentYear - postDate.getYear();
                Memory* memory = dynamic_cast<Memory*>(post);
                cout << "--- " << currentUser->getName() << " shared a memory ---" << endl;
                cout << "\"" << memory->getMemoryDescription() << "\"" << endl;
                cout << "(" << postDate.toString() << ")" << endl;
                cout << "(" << yearsElapsed << " " << (yearsElapsed == 1 ? "Year" : "Years") << " Ago)" << endl;
                cout << endl << "--- Original Post ---" << endl;
                Post* originalPost = memory->getOriginalPost();
                displayPost(*originalPost);
            }
        }
    }
    if (!foundMemory) {
        cout << "You don't have any memories yet." << endl;
    }
}

void SocialNetworkApp::shareMemory(const string& postID, const string& text) {
    Post** timeline = currentUser->getTimeline();
    int numPosts = currentUser->getNumPosts();

    int currentDay = currentDate.getDay();
    int currentMonth = currentDate.getMonth();

    for (int i = 0; i < numPosts; i++) {
        Post* post = timeline[i];
        Date postDate = post->getSharedDate();

        if (postDate.getDay() == currentDay && postDate.getMonth() == currentMonth) {
            Memory* memory = new Memory("memoryID", text, postDate, post);

            currentUser->addToTimeline(memory);

            cout << "Memory shared successfully!" << endl;

            return;
        }
    }
    cout << "No post found with the current day and month." << endl;
}

void SocialNetworkApp::likePagePost(const string& pageID, const string& postID, User* user) {
    Page* page = nullptr;
    for (int i = 0; i < numPages; i++) {
        if (pageList[i]->getPageID() == pageID) {
            page = pageList[i];
            break;
        }
    }
    if (page != nullptr) {
        Post* post = page->findPost(postID);
        if (post != nullptr) {
            if (post->isLikedBy(user)) {
                cout << "You have already liked this post." << endl;
            }
            else {
                post->addLike(user);
                cout << "You liked the post with ID " << postID << " on page " << pageID << "." << endl;
            }
        }
        else {
            cout << "Post with ID " << postID << " not found on page " << pageID << "." << endl;
        }
    }
    else {
        cout << "Page with ID " << pageID << " not found." << endl;
    }
}

void SocialNetworkApp::addPost(const string& description, const string& activityType, const string& activityValue) {
    if (currentUser == nullptr) {
        cout << "No user is currently logged in." << endl;
        return;
    }
    string postID = "post" + to_string(currentUser->getNumPosts() + 1);

    Date currentDate = this->currentDate;

    Activity activity(activityType, activityValue);

    Post* post = new Post(postID, description, currentDate, activity);

    currentUser->addToTimeline(post);
    cout << "Post added successfully to your timeline." << endl;
}

void SocialNetworkApp::addUser(const string& userID, const string& name) {
    User* newUser = new User(userID, name);

    User** newList = new User * [numUsers + 1];

    for (int i = 0; i < numUsers; i++) {
        newList[i] = userList[i];
    }

    newList[numUsers] = newUser;

    delete[] userList;
    userList = newList;

    ++numUsers;
}