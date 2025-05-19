// #include <time.h>
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
    char borrowed_book[6][200];  // 记录借阅书名
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
    int lent_account;  // 记录借阅用户数量
    char lent_user[61][200];  // 记录借阅用户
    struct book *next;
} *BookPtr, Book;  // 书籍链表

// typedef struct {
//     int userID;          // 用户ID
//     int bookID;          // 图书ID
//     time_t borrowDate;   // 借书日期
//     time_t dueDate;      // 应还日期
//     time_t returnDate;   // 实际归还日期（0表示未归还）
//     float penaltyFee;    // 罚金金额
//     int isPaid;         // 是否已缴纳罚金
// } BorrowRecord;

// 菜单函数
void screen_clear();//清屏函数
int HomeMenu();//主菜单
int AdminAMenu();//管理员菜单
int UserMenu();  // 用户菜单
//管理员函数
void Showbook(BookPtr head);  // 显示所有书籍信息
void ShowBookInfo(BookPtr head);//显示单本书借阅信息
void Showuser(UserPtr head);//显示所有用户信息
void addBook(BookPtr head);//添加书籍信息
void searchBook(BookPtr head);//搜索函数
BookPtr Delbook(BookPtr head);  // 删除书籍信息，返回新的链表头替换原链表头
void ModifyBook(BookPtr head);//修改书籍信息
// 用户函数
void ShowUserInfo(UserPtr head, int user_id);//显示个人信息
void BorrowBook(BookPtr book_head, UserPtr user_head, int user_id);//借书函数
void ReturnBook(BookPtr book_head, UserPtr user_head, int user_id);  // 还书函数
void ModifyUserInfo(UserPtr head,int user_id);//修改个人信息
// 注册和登陆校验
UserPtr addUser(UserPtr head,int *current_id);  // 注册用户
void Login(int n, UserPtr head,int *user_id);//管理员和用户登陆函数（传账号密码）
int ExistUser(UserPtr head, int user_id, char *password);//验证用户登录
//文件读写
UserPtr read_users_from_file(const char *filename,int *current_id);  // 读取用户信息
BookPtr read_books_from_file(const char *filename);  // 读取书籍信息
void write_users_to_file(const char* filename, UserPtr head,int id); // 写入用户信息
void write_books_to_file(const char *filename, BookPtr head);  // 写入书籍信息

