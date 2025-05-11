#define _CRT_SECURE_NO_WARNINGS 1
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void screen_clear()
{
    printf("\033[2J\033[H");  // ANSI 清屏序列
}  // 清屏函数

/* 菜单类函数 */
int HomeMenu()
{
    screen_clear();

    int n;
    printf("\t-----------------------\n");
    printf("\t欢迎进入图书管理系统 \n");
    printf("\t-----------------------\n");
    printf("1.管理员登录 2.用户登录 3.注册 4.退出\n");
    printf("请选择：");
    scanf("%d", &n);
    return n;
}  // 菜单一 ：首页菜单

int AdminMenu()
{
    screen_clear();

    getchar();  // 清除可能存在的换行符
    int n;
    printf("\t-------------\n");
    printf("\t 欢迎管理员\n");
    printf("\t-------------\n");
    printf(
        "1.查看所有图书 2.添加图书 3.注销图书 4.修改图书 5.管理用户 "
        "6.图书查询7.返回主菜单\n");
    printf("请选择：");
    scanf("%d", &n);
    return n;
}  // 菜单二：管理员菜单

int UserMenu()
{
    screen_clear();
    int n;
    printf("\t\t----------------\n");
    printf("\t\t    欢迎用户\n");
    printf("\t\t----------------\n");
    printf("1.显示所有图书 2.个人管理 3.借阅图书 4.归还图书 5.返回主菜单\n");
    printf("请选择：\n");
    scanf("%d", &n);
    return n;
}  // 菜单三：用户菜单

/* 主菜单部分 */

int ExistUser(UserPtr head, int user_id, char *password)
{
    UserPtr p = head;
    while (p != NULL &&
           ((p->id != user_id) || (strcmp(p->password, password) != 0)))
    {
        p = p->next;
    }  // 遍历user链表，查找用户名和密码匹配的节点

    if (!p)
        return 0;
    else
    {
        return 1;
    }
}

void Login(int n, UserPtr head, int *user_id)
{
    char account[200];
    int id;
    char password[200];
    if (n == 1)  // 管理员
    {
        printf("请输入管理员账号名：");
        scanf("%s", account);
        printf("请输入密码：");
        scanf("%s", password);
        if (strcmp(account, ADMIN) != 0 || strcmp(password, ADMINPASS) != 0)
        {
            printf("账号密码错误，自动退出！\n");
            exit(0);
        }  // 管理员校验
    }
    else if (n == 2)  // 用户
    {
        printf("请输入登陆id：");
        scanf("%d", &id);
        printf("请输入密码：");
        scanf("%s", password);
        if (ExistUser(head, id, password))
        {
            *user_id = id;
        }
        else
        {
            printf("账号密码错误，自动退出！\n");
            exit(0);
        }
    }
    else
    {
        exit(0);
    }
}  // 登录模块
UserPtr addUser(UserPtr head, int *current_id)
{
    screen_clear();

    UserPtr p = head;
    while (p != NULL && p->next != NULL)
    {
        p = p->next;
    }  // 找到user链表最后一个节点

    UserPtr pnew = (UserPtr)malloc(sizeof(User));
    pnew->next = NULL;

    pnew->id = *current_id;  // 分配用户ID
    (*current_id)++;         // 更新最新可分配ID

    printf("请输入注册信息：\n");
    printf("姓名：");
    scanf("%s", pnew->Username);  // 会在缓冲区残留换行符
    getchar();                    // 从输入缓冲区中读取并丢弃一个字符

    printf("性别：");
    scanf("%s", pnew->Sex);
    getchar();

    printf("年龄：");
    scanf("%s", pnew->Old);
    getchar();

    printf("联系电话：");
    scanf("%s", pnew->Tel);
    getchar();

    printf("注册密码：");
    scanf("%s", pnew->password);

    pnew->borrowed_account = 0;  // 初始化借阅数量为0

    if (p == NULL)  // 若链表为空
    {
        return pnew;
    }
    // 尾插接入user链表
    p->next = pnew;

    return head;
}  // 用户注册模块

void Showbook(BookPtr head)
{
    screen_clear();

    if (head == NULL)
    {
        printf("\t没有图书信息\n");
    }
    else
    {
        printf("\t(图书信息如下):\n");
        BookPtr pshow = (BookPtr)malloc(sizeof(Book));
        BookPtr tmp = pshow;  // 记录这个临时结点
        pshow->next = head;
        printf(
            "------------------------------------------------------------------"
            "---"
            "----------"
            "---"
            "---\n");
        printf("编号\t\t书名\t\t作者\t\t出版社\t\t总数\t\t在馆数\n");
        printf(
            "------------------------------------------------------------------"
            "---"
            "----------"
            "---"
            "---\n");
        while ((pshow->next) != NULL)
        {
            printf("%-16s", pshow->next->ISBN);
            printf("%-16s", pshow->next->BookName);
            printf("%-16s", pshow->next->Writer);
            printf("%-16s", pshow->next->Press);
            printf("%-16d", pshow->next->total);
            printf("%-16d", pshow->next->stock);

            printf("\n");
            pshow = pshow->next;
        }
        free(tmp);  // 释放临时结点

        printf("\n是否查看单本书籍借阅信息？(y键确定,其他键退出)：");
        char op;
        getchar();  // 清除换行符
        scanf("%c", &op);
        if (op == 'y')
        {
            ShowBookInfo(head);
        }
    }
    printf("\n查看完成\n");
}

void ShowBookInfo(BookPtr head)
{
    printf("请输入要查看的书籍ISBN：");
    char ISBN[200];
    scanf("%s", ISBN);
    BookPtr p = head;
    while (p != NULL && strcmp(p->ISBN, ISBN) != 0)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        printf("无此书\n");
        return;
    }
    else if (p->lent_account == 0)
    {
        printf("暂无借阅者信息\n");
        return;
    }
    printf("借阅者信息如下：\n");
    for (int i = 0; i < p->lent_account; i++)
    {
        printf("%s ", p->lent_user[i]);
    }
}  // 显示单本书信息

void Showuser(UserPtr head)
{
    screen_clear();

    if (head == NULL)
        printf("\t*暂无普通用户信息*\n");
    else
    {
        printf("遍历结果为:\n");
        UserPtr pshow = (UserPtr)malloc(sizeof(User));
        UserPtr tmp = pshow;  // 记录这个临时结点
        pshow->next = head;
        printf(
            "\t----------------------------------------------------------------"
            "-----"
            "---"
            "-----"
            "---\n");
        printf("\tid\t姓名\t\t性别\t\t年龄\t\t电话\t\t已借阅书籍数\n");
        printf(
            "\t----------------------------------------------------------------"
            "-----"
            "---"
            "-----"
            "---\n");
        while ((pshow->next) != NULL)
        {
            printf("\t%d ", pshow->next->id);
            printf("\t%s ", pshow->next->Username);
            printf("\t\t%s", pshow->next->Sex);
            printf("\t\t%s", pshow->next->Old);
            printf("\t\t%s", pshow->next->Tel);
            printf("\t\t%d", pshow->next->borrowed_account);
            printf("\n");
            pshow = pshow->next;
        }
        free(tmp);  // 释放临时结点
    }
    printf("\t查看完成\n");
}  // 打印用户模块

void addBook(BookPtr head)
{
    screen_clear();

    BookPtr p = head;
    while (p->next != NULL)
    {
        p = p->next;
    }  // 找到book链表最后一个节点

    BookPtr pnew = (BookPtr)malloc(sizeof(Book));
    printf("请输入书编号：");
    scanf("%s", pnew->ISBN);
    getchar();
    printf("请输入书名：");
    scanf("%s", pnew->BookName);
    getchar();
    printf("请输入书作者：");
    scanf("%s", pnew->Writer);
    getchar();
    printf("请输入书籍出版社：");
    scanf("%s", pnew->Press);
    getchar();
    int stock = 0;
    printf("请输入购入总数：");
    scanf("%d", &stock);
    pnew->stock = stock;
    pnew->total = stock;  // 初始化库存和总数
    getchar();

    pnew->next = p->next;
    p->next = pnew;
    printf("添加成功\n");
}  // 添加书籍模块

BookPtr Delbook(BookPtr head)
{
    screen_clear();

    char s1[200];
    printf("请输入要删除的书籍的ISBN：\n");
    scanf("%s", s1);
    BookPtr dummy = (BookPtr)malloc(sizeof(Book));
    dummy->next = head;
    BookPtr pre = dummy;
    while (pre->next != NULL && strcmp((pre->next->ISBN), s1) != 0)
    {
        pre = pre->next;
    }
    if (pre->next != NULL)
    {
        BookPtr pdel = pre->next;  // 要删除的结点
        pre->next = pdel->next;    // 将要删除的结点从链表中断开
        free(pdel);                // 释放要删除的结点
        printf("\t删除完成\n");
    }
    else  // 没有找到要删除的书籍编号
    {
        printf("无此书\n");
    }
    head = dummy->next;  // 更新头结点
    free(dummy);         // 释放哑结点
    return head;
}  // 注销书籍模块

void ModifyBook(BookPtr head)
{
    screen_clear();
    char s1[200];
    printf("请输入要修改的书籍的ISBN：\n");
    scanf("%s", s1);
    BookPtr p = head;
    while (p != NULL && strcmp((p->ISBN), s1) != 0)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        printf("无此书\n");
        return;
    }
    else
    {
        printf("请输入修改后的书籍信息：\n");
        printf("ISBN：");
        scanf("%s", p->ISBN);
        getchar();
        printf("书名：");
        scanf("%s", p->BookName);
        getchar();
        printf("作者：");
        scanf("%s", p->Writer);
        getchar();
        printf("出版社：");
        scanf("%s", p->Press);
        getchar();
        printf("总数：");
        scanf("%d", &p->total);
        getchar();
        printf("在馆数：");
        scanf("%d", &p->stock);
    }
}

void ShowUserInfo(UserPtr head, int user_id)
{
    screen_clear();
    UserPtr pshow = head;
    while (pshow != NULL && pshow->id != user_id)
        pshow = pshow->next;  // 查找对应的用户
    printf("欢迎您，用户%d\n", user_id);
    if (pshow->borrowed_account == 0)
        printf("您没有借阅书籍\n");
    else
    {
        printf("您已借阅的书籍有：\n");
        for (int i = 0; i < pshow->borrowed_account; i++)
        {
            printf("%s ", pshow->borrowed_book[i]);
        }
        printf("\n");
    }
}  // 用户个人信息
void ModifyUserInfo(UserPtr head, int user_id)
{
    screen_clear();
    UserPtr p = head;
    while (p != NULL && p->id != user_id)
        p = p->next;  // 查找对应的用户
    printf("欢迎您，用户%d\n", user_id);
    printf("请输入新的密码：");
    scanf("%s", p->password);
    printf("修改成功！\n");
}

void BorrowBook(BookPtr book_head, UserPtr user_head, int user_id)
{
    screen_clear();

    char borrowISBN[200];
    Showbook(book_head);  // 显示可借书目
    printf("输入要借阅的ISBN: ");
    scanf("%s", borrowISBN);

    // 查找书籍和用户
    BookPtr pbook = book_head;
    UserPtr puser = user_head;
    while (puser != NULL && puser->id != user_id)
        puser = puser->next;
    while (pbook != NULL && strcmp(pbook->ISBN, borrowISBN) != 0)
        pbook = pbook->next;
    // 验证逻辑
    if (!pbook || !puser)
        printf("未找到书籍或用户\n");
    else if (pbook->stock <= 0)
        printf("库存不足\n");
    else if (puser->borrowed_account >= 5)
        printf("已达借阅上限\n");
    else
    {
        // 更新数据
        strcpy(puser->borrowed_book[puser->borrowed_account],
               pbook->BookName);  // 将借阅的书籍ISBN存入用户信息中
        strcpy(pbook->lent_user[pbook->lent_account],
               puser->Username);  // 将借阅的用户存入书籍信息中
        puser->borrowed_account++;
        pbook->stock--;
        pbook->lent_account++;
        printf("借阅成功！剩余库存：%d\n", pbook->stock);
    }
}
void ReturnBook(BookPtr book_head, UserPtr user_head, int user_id)
{
    screen_clear();

    ShowUserInfo(user_head, user_id);
    char book[200];
    printf("输入要归还的书名（带书名号）: ");
    scanf("%s", book);

    // 查找书籍和用户
    BookPtr pbook = book_head;
    UserPtr puser = user_head;
    while (puser != NULL && puser->id != user_id)
        puser = puser->next;
    while (pbook != NULL && strcmp(pbook->BookName, book) != 0)
        pbook = pbook->next;
    // 验证逻辑
    if (!pbook || !puser)
        printf("未找到书籍或用户\n");
    else if (puser->borrowed_account <= 0)
        printf("没有借阅记录\n");
    else
    {
        // 更新数据
        pbook->stock++;
        puser->borrowed_account--;
        printf("归还成功！剩余库存：%d\n", pbook->stock);
    }
}

UserPtr read_users_from_file(const char *filename,
                             int *current_id)  // 尾插法，最后传回头节点
{
    FILE *file = fopen(filename, "r");

    UserPtr head = NULL, tail = NULL;
    UserPtr p;
    if (fscanf(file, "%d", current_id) != 1)
    {
        *current_id = 1000;  // 如果文件为空，初始化ID为1000
        return head;
    }

    while (!feof(file))
    {
        p = (UserPtr)malloc(sizeof(User));
        p->next = NULL;
        // 基础字段解析
        if (fscanf(file, "%d %s %s %s %s %s %d", &p->id, p->Username, p->Sex,
                   p->Old, p->Tel, p->password, &p->borrowed_account) != 7)
        {
            free(p);
            break;
        }

        // 动态解析书名（逐个读取剩余字段）
        for (int i = 0; i < p->borrowed_account; i++)
        {
            fscanf(file, "%s", p->borrowed_book[i]);
        }

        // 尾插法构建链表
        if (!head)
            head = tail = p;
        else
            tail->next = p, tail = p;
    }
    fclose(file);
    return head;
}  // 读取用户信息
BookPtr read_books_from_file(const char *filename)
{
    FILE *file = fopen(filename, "r");

    BookPtr head = NULL, tail = NULL;
    BookPtr p = (BookPtr)malloc(sizeof(Book));
    while (!feof(file))
    {
        p = (BookPtr)malloc(sizeof(Book));
        p->next = NULL;
        // 基础字段解析
        if (fscanf(file, "%s %s %s %s %d %d %d", p->ISBN, p->BookName,
                   p->Writer, p->Press, &p->total, &p->stock,
                   &p->lent_account) != 7)
        {
            free(p);
            break;
        }

        // 动态解析借阅者（逐个读取剩余字段）
        for (int i = 0; i < p->lent_account; i++)
        {
            fscanf(file, "%s", p->lent_user[i]);
        }

        // 尾插法构建链表
        if (!head)
            head = tail = p;
        else
            tail->next = p, tail = p;
    }
    fclose(file);
    return head;
}  // 读取书籍信息

void write_users_to_file(const char *filename, UserPtr head, int id)
{
    FILE *file = fopen(filename, "w");
    // 写入最新的用户ID
    fprintf(file, "%d\n", id);

    UserPtr p = head;
    while (p != NULL)
    {
        // 基础信息写入
        fprintf(file, "%d %s %s %s %s %s %d\n", p->id, p->Username, p->Sex,
                p->Old, p->Tel, p->password, p->borrowed_account);
        // 借阅信息写入
        for (int i = 0; i < p->borrowed_account; i++)
        {
            fprintf(file, " %s", p->borrowed_book[i]);
        }

        fprintf(file, "\n");  // 结束当前用户记录
        p = p->next;
    }
    fclose(file);
}  // 写入用户信息
void write_books_to_file(const char *filename, BookPtr head)
{
    FILE *file = fopen(filename, "w");
    BookPtr p = head;
    while (p != NULL)
    {
        // 基础信息写入
        fprintf(file, "%s %s %s %s %d %d %d\n", p->ISBN, p->BookName, p->Writer,
                p->Press, p->total, p->stock, p->lent_account);
        // 借阅信息写入
        for (int i = 0; i < p->lent_account; i++)
        {
            fprintf(file, " %s", p->lent_user[i]);
        }
        fprintf(file, "\n");  // 结束当前书籍记录
        p = p->next;
    }
    fclose(file);
}  // 写入书籍信息

int main()
{
    int ChoiceMainMenu, ChoiceSubMenu, continueOperation;
    int *current_id = (int *)malloc(sizeof(int));
    UserPtr userList =
        read_users_from_file("user.txt", current_id);     // 读取用户表
    BookPtr bookList = read_books_from_file("book.txt");  // 读取书籍表

    while ((ChoiceMainMenu = HomeMenu()))
    {
        if (ChoiceMainMenu == 3)
        {  // 主菜单序号3跳转注册模块
            printf("\t欢迎注册本软件\n");
            userList = addUser(userList, current_id);
            printf("注册成功！您的登陆ID为：%d\n", *current_id - 1);
            char nextStep = '1';
            while (nextStep != 'y')
            {
                printf("记住后请输入y：");
                scanf(" %c", &nextStep);
            }
        }
        else if (ChoiceMainMenu == 4)
        {
            break;
        }
        else  // 登陆模块
        {
            int *user_id = (int *)malloc(sizeof(int));  // 接收用户当前id
            Login(ChoiceMainMenu, userList, user_id);   // 先进行身份验证

            if (ChoiceMainMenu == 1)
            {  // 菜单二序号1管理员登录
                ChoiceSubMenu = AdminMenu();
                while (ChoiceSubMenu)
                {  // n2=管理员菜单序号
                    switch (ChoiceSubMenu)
                    {
                        case 1:
                            Showbook(bookList);  // 列出书籍信息
                            break;
                        case 2:
                            addBook(bookList);  // 添加书籍信息
                            break;
                        case 3:
                            bookList = Delbook(bookList);  // 删除书籍信息
                            break;
                        case 4:
                            ModifyBook(bookList);
                            break;
                        case 5:
                            Showuser(userList);  // 列出用户信息
                            break;
                        case 6:
                            break;
                        default:
                            break;
                    }
                    printf("继续在当前菜单中进行选择(1确定 0退出)：");
                    scanf("%d", &continueOperation);
                    if (continueOperation == 1)
                    {
                        ChoiceSubMenu = AdminMenu();
                    }
                    else if (continueOperation == 0)
                    {
                        break;
                    }
                }
            }
            else if (ChoiceMainMenu == 2)
            {  // 菜单一序号2用户登录
                ChoiceSubMenu = UserMenu();
                while (ChoiceSubMenu)
                {
                    switch (ChoiceSubMenu)
                    {
                        case 1:
                            Showbook(bookList);  // 列出书籍信息
                            break;
                        case 2:
                            ShowUserInfo(userList, *user_id);
                            printf("是否要修改密码？(1确定 0退出)：");
                            scanf("%d", &continueOperation);
                            if (continueOperation == 1)
                            {
                                ModifyUserInfo(userList, *user_id);
                            }
                            break;
                        case 3:
                            BorrowBook(bookList, userList, *user_id);
                            break;
                        case 4:
                            ReturnBook(bookList, userList, *user_id);
                            break;
                        default:
                            break;
                    }
                    printf("要退出登陆吗？(1确定 0取消)：");
                    scanf("%d", &continueOperation);
                    if (continueOperation == 0)
                    {
                        ChoiceSubMenu = UserMenu();
                    }
                    else if (continueOperation == 1)
                    {
                        break;
                    }
                }
            }
            else
            {
                continue;
            }
        }
    }
    // 将数据写入文件
    write_users_to_file("user.txt", userList, *current_id);
    write_books_to_file("book.txt", bookList);
    return 0;
}
