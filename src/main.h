#define _CRT_SECURE_NO_WARNINGS 1
#define ADMIN "admin"
#define ADMINPASS "123"
typedef struct user
{
	int id;//唯一的用户标识，用户名可能会重复
    char Username[200];
    char Sex[100];
    char Old[20];
    char Tel[15];
    char password[20];
    int borrowed_account;  // 记录借阅数量
    char borrowed_ISBN[6][200];//改成书名比较好找
    struct user *next;
} *UserPtr, User;  // 用户链表

typedef struct book
{
    char ISBN[20];
    char BookName[200];
    char Writer[200];
    char Press[200];
    int total;
    int stock;
    struct book *next;
} *BookPtr, Book;  // 书籍链表


// 菜单函数
void screen_clear();//清屏函数
int HomeMenu();//主菜单
int AdminAMenu();//管理员菜单
int UserMenu();  // 用户菜单
//管理员函数
void Showbook(BookPtr head);//显示书籍信息
void Showuser(UserPtr head);//显示用户信息
void addBook(BookPtr head);//添加书籍信息
BookPtr Delbook(BookPtr head);  // 删除书籍信息，返回新的链表头替换原链表头
void ModifyBook(BookPtr head);//修改书籍信息
// 用户函数
void ShowUserInfo(UserPtr head, char *username);//显示用户信息
void BorrowBook(BookPtr book_head, UserPtr user_head, char *username);//借书函数
void ReturnBook(BookPtr book_head, UserPtr user_head, char *username);  // 还书函数
void ModifyUserInfo(UserPtr head,char *username);//修改个人信息
// 注册和登陆校验
UserPtr addUser(UserPtr head);  // 注册用户
char* Login(int n, UserPtr head,char *username);//管理员和用户登陆函数（传账号密码）
int ExistUser(UserPtr head, char *username, char *password);//验证用户登录
void Admin_or_User(char user_account[], char password[], int n, UserPtr head);//验证身份
//文件读写
UserPtr read_users_from_file(const char *filename);  // 读取用户信息
BookPtr read_books_from_file(const char *filename);  // 读取书籍信息
void write_users_to_file(const char* filename, UserPtr head); // 写入用户信息
void write_books_to_file(const char *filename, BookPtr head);  // 写入书籍信息

