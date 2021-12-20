//
//  main.c
//  餐厅点餐系统
//
//  Created by 金剑侠 on 2021/1/4.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//记录商店在售菜品
typedef struct {
    char number[10]; /* 菜的编号 */
    char name[20]; /* 菜名 */
    int price; /* 价格 */
    int count; /* 剩余数量 */
} Store;

//记录餐桌信息
typedef struct {
    int l; /* 8人桌 */
    int m; /* 4人桌 */
    int s; /* 2人桌 */
} Table;

typedef struct {
    Store data[100];
    int length;
    Table table;
    Table tableCount;
} List;

//登陆界面
void Index(void);

//用户界面
void Usermode(void);

//管理员登陆界面
void ManagerSignIn(void);

//管理员界面
void Managermode(void);

//点菜界面
void buy(void);

//显示所有菜品信息
void ShowAll(void);

//按价格升序排序
void InsertUp(void);

//增加菜品
void CreateDish(void);

//删除菜品
void DeleteDish(void);

//查询菜品信息
void ReadDish(void);

//修改菜品信息
void UpdateDish(void);

//增加餐桌数量
void AddTable(void);

//减少餐桌数量
void DeleteTable(void);

//查询餐桌数量
void ReadTable(void);

//打烊（将剩余餐桌数量置为餐厅拥有的餐桌数量）
void Void(void);

//读取数据
void Read(List *list);

//保存数据
void Save(List list);

int main() {
    Index();
}

void Index(void) {
    printf("世纪王朝大沙县小吃\n");
    printf("1.用户\n");
    printf("2.管理员\n");
    printf("0.退出\n");
    printf("请输入序号进入系统：\n");
    int i;
    while (1) {
        scanf("%d", &i);
        switch (i) {
            case 1:
                Usermode();
                break;
            case 2:
                ManagerSignIn();
                break;
            case 0:
                Void();
                exit(0);
            default:
                printf("输入无效，请重新输入！\n");
        }
    }
}

void Usermode(void) {
    List list;
    Read(&list);
    printf("用户界面\n");
    printf("欢迎光临，请问你们有几位客人？（返回上一层请直接输入0）\n");
    int i;
    scanf("%d", &i);
    if (i == 0) {
        Index();
    } else if (i <= 2 && list.table.s > 0) {
        list.table.s--;
    } else if (i <= 4 && list.table.m > 0) {
        list.table.m--;
    } else if (i <= 8 && list.table.l > 0) {
        list.table.l--;
    } else {
        printf("没有座位了，另寻出路吧！\n");
        Void();
        exit(0);
    }
    Save(list);
    printf("已为您安排好了一张餐桌，请就坐。\n");
    while (1) {
        printf("有什么能为你效劳的吗？\n");
        printf("1.显示菜单\n");
        printf("2.按价格升序排序\n");
        printf("3.开始点菜\n");
        printf("0.返回上一层\n");
        scanf("%d", &i);
        switch (i) {
            case 1:
                ShowAll();
                break;
            case 2:
                InsertUp();
                ShowAll();
                break;
            case 3:
                ShowAll();
                buy();
                Index();
                break;
            case 0:
                Index();
                break;
            default:
                printf("输入无效，请重新输入！\n");
        }
    }
}

void ManagerSignIn(void) {
    char name[10];
    char password[20];
    while (1) {
        printf("请输入账号：\n");
        scanf("%s", name);
        printf("请输入密码：\n");
        scanf("%s", password);
        if (!(strcmp(password, "password123")) && !(strcmp(name, "root"))) {
            printf("登陆成功！\n");
            Managermode();
        } else {
            printf("账号或密码错误！请重新输入！\n");
        }
    }
}

void Managermode(void) {
    int i;
    while (1) {
        printf("管理员界面\n");
        printf("1.添加菜品\n");
        printf("2.删除菜品\n");
        printf("3.查询菜品信息\n");
        printf("4.修改菜品信息\n");
        printf("5.增加餐桌数量\n");
        printf("6.减少餐桌数量\n");
        printf("7.查询餐桌数量\n");
        printf("8.打烊\n");
        printf("0.返回上一层\n");
        scanf("%d", &i);
        switch (i) {
            case 1:
                ShowAll();
                CreateDish();
                break;
            case 2:
                ShowAll();
                DeleteDish();
                break;
            case 3:
                ShowAll();
                ReadDish();
                break;
            case 4:
                ShowAll();
                UpdateDish();
                break;
            case 5:
                AddTable();
                break;
            case 6:
                DeleteTable();
            case 7:
                ReadTable();
            case 8:
                Void();
                printf("已请出所有客人！\n");
                exit(0);
            case 0:
                Index();
                break;
            default:
                printf("输入无效，请重新输入！\n");
        }
    }
}

void buy(void) {
    List list;
    Read(&list);
    int total = 0;
    int i, j, flag;
    printf("请输入菜品的序号进行挑选（挑选完毕的话可以输入0结束购买）：\n");
    char input[10];
    while (1) {
        flag = 0;
        scanf("%s", input);
        if (!(strcmp(input, "0"))) {
            break;
        }
        for (i = 0; i < list.length; ++i) {
            if (!(strcmp(list.data[i].number, input)) && list.data[i].count > 0) {
                flag = 1;
                list.data[i].count--;
                total += list.data[i].price;
                printf("这边帮您记录下了，现总计消费金额%d元，请问还有什么需要的呢？（点菜完毕请直接输入0）\n", total);
            }
        }
        if (flag == 0) {
            printf("不好意思这道菜卖得太好，暂时没有了，客人可以试着点别的菜哦。（点菜完毕请直接输入0）\n");
        }
    }
    if (total == 0) {
        printf("看来这里没有客人想要的菜品，那祝客人一路走好！\n");
    } else {
        printf("好的客人，您消费的金额是%d元，请支付！\n", total);
        while (1) {
            scanf("%d", &j);
            if (j > total) {
                printf("支付成功，为您找零%d元，祝您生活愉快！\n", j - total);
                break;
            } else if (j == total) {
                printf("支付成功，祝您生活愉快！\n");
                break;
            }
            if (j < total) {
                total -= j;
                printf("您好客人，还需要支付%d元！\n", total);
            }
        }
    }
    Save(list);
}

void ShowAll(void) {
    List list;
    Read(&list);
    printf("序号\t菜名\t价格\t剩余数量\n");
    for (int i = 0; i < list.length; i++) {
        printf("%s %s %d %d\n", list.data[i].number, list.data[i].name,
               list.data[i].price, list.data[i].count);
    }
    printf("菜单已展示完毕！\n");
}

void InsertUp(void) {
    List list;
    Read(&list);
    int i, j;
    Store temp;
    for (i = 1; i < list.length; ++i) {
        temp = list.data[i];
        for (j = i - 1; j >= 0; j--) {
            if (temp.price < list.data[j].price) {
                list.data[j + 1] = list.data[j];
                list.data[j] = temp;
            }
        }
    }
    printf("菜单已按照价格升序排序！\n");
    Save(list);
}

void CreateDish(void) {
    List list;
    Read(&list);
    char text[10];
    int i, flag;
    printf("按以下顺序输入您想引进的新菜品的序号：（返回上一层请直接输入0）\n");
    while (1) {
        flag = 1;
        scanf("%s", text);
        if (!(strcmp(text, "0"))) {
            break;
        }
        for (i = 0; i < list.length; ++i) {
            if (!(strcmp(text, list.data[i].number))) {
                flag = 0;
                printf("序号发现重复，请重新输入！\n");
            }
        }
        if (flag == 1) {
            printf("请按顺序输入1.菜名2.价格3.数量\n");
            strcpy(list.data[list.length].number, text);
            scanf("%s%d%d", list.data[list.length].name, &(list.data[list.length].price),
                  &(list.data[list.length].count));
            list.length++;
            printf("添加成功！\n");
        }
        printf("继续输入可以继续添加，返回上一层请输入0。\n");
    }
    Save(list);
    Managermode();
}

void DeleteDish(void) {
    List list;
    Read(&list);
    char number[10];
    ShowAll();
    printf("请输入您想删除的菜品序号：（返回上一层请直接输入0）\n");
    while (1) {
        scanf("%s", number);
        if (!(strcmp(number, "0"))) {
            Managermode();
        }
        for (int i = 0; i < list.length; i++) {
            if (!strcmp(list.data[i].number, number)) {
                for (int j = i; j < list.length; j++) {
                    list.data[j] = list.data[j + 1];
                }
                list.length--;
                printf("删除成功！\n");
                break;
            }
        }
        printf("继续输入可以继续删除，返回上一层请直接输入0\n");
        Save(list);
    }

}

void ReadDish(void) {
    List list;
    Read(&list);
    int i;
    char number[10];
    printf("请输入您想查询菜品的序号：（返回上一层请直接输入0）\n");
    while (1) {
        scanf("%s", number);
        if (!(strcmp(number, "0"))) {
            Managermode();
        }
        for (i = 0; i < list.length; i++) {
            if (!strcmp(list.data[i].number, number)) {
                printf("找到了！\n");
                printf("%s %s %d %d\n", list.data[i].number, list.data[i].name, list.data[i].price, list.data[i].price);
                break;
            }
        }
        if (i == list.length) {
            printf("没有找到！\n");
        }
        printf("继续输入可以继续查找，返回上一层请直接输入0\n");
    }
}

void UpdateDish(void) {
    List list;
    Read(&list);
    char number[10];
    printf("请输入您想修改菜品的序号：（返回上一层请直接输入0）\n");
    while (1) {
        scanf("%s", number);
        if (!(strcmp(number, "0"))) {
            break;
        }
        for (int i = 0; i < list.length; i++) {
            if (!strcmp(list.data[i].number, number)) {
                printf("请问您想将下列信息修改为什么？\n");
                printf("%s %s %d %d\n", list.data[i].number, list.data[i].name, list.data[i].price, list.data[i].price);
                scanf("%s%s%d%d", list.data[i].number, list.data[i].name, &(list.data[i].price), &(list.data[i].count));
                printf("%s号菜品信息已更新完成！\n", number);
                break;
            }
        }
        printf("继续输入可以继续修改，返回上一层请直接输入0\n");
    }
    Save(list);
    Managermode();
}

void AddTable(void) {
    List list;
    Read(&list);
    int text, number;
    printf("请问您想添加桌子的类型及其数量：（返回上一层请直接输入0）\n");
    printf("1.双人桌\n");
    printf("2.四人桌\n");
    printf("3.八人桌\n");
    printf("0.返回上一层\n");
    while (1) {
        scanf("%d", &text);
        if (text == 0) {
            break;
        }
        scanf("%d", &number);
        if (text == 1) {
            list.tableCount.s += number;
            printf("已完成添加%d张双人桌！\n", number);
        } else if (text == 2) {
            list.tableCount.m += number;
            printf("已完成添加%d张四人桌！\n", number);
        } else if (text == 3) {
            list.tableCount.l += number;
            printf("已完成添加%d张八人桌！\n", number);
        }
        printf("继续输入可以继续添加，返回上一层请直接输入0\n");
    }
    Save(list);
    Managermode();
}

void DeleteTable(void) {
    List list;
    Read(&list);
    int text, number;
    printf("请问您想移除桌子的类型及其数量：（返回上一层请直接输入0）\n");
    printf("1.双人桌\n");
    printf("2.四人桌\n");
    printf("3.八人桌\n");
    printf("0.返回上一层\n");
    while (1) {
        scanf("%d", &text);
        if (text == 0) {
            break;
        }
        scanf("%d", &number);
        if (text == 1 && number <= list.tableCount.s) {
            list.tableCount.s -= number;
            printf("已完成移除%d张双人桌！\n", number);
        } else if (text == 1 && number > list.tableCount.s) {
            printf("移除失败，我们餐厅没有那么多双人桌！\n");
        } else if (text == 2 && number <= list.tableCount.m) {
            list.tableCount.m -= number;
            printf("已完成移除%d张双人桌！\n", number);
        } else if (text == 2 && number > list.tableCount.m) {
            printf("移除失败，我们餐厅没有那么多四人桌！\n");
        } else if (text == 3 && number <= list.tableCount.l) {
            list.tableCount.l -= number;
            printf("已完成移除%d张双人桌！\n", number);
        } else if (text == 3 && number > list.tableCount.l) {
            printf("移除失败，我们餐厅没有那么多八人桌！\n");
        }
        printf("继续输入可以继续移除，返回上层请直接输入0\n");
    }
    Save(list);
    Managermode();
}

void ReadTable(void) {
    List list;
    Read(&list);
    int i = 1;
    printf("当前剩余的双人桌数量为%d张，四人桌数量为%d张，八人桌数量为%d张。\n", list.table.s, list.table.m, list.table.l);
    printf("当前餐厅拥有的双人桌数量为%d张，四人桌数量为%d张，八人桌数量为%d张。\n", list.tableCount.s, list.tableCount.m, list.tableCount.l);
    printf("返回上一层请输入0：\n");
    while (i) {
        scanf("%d", &i);
    }
    Managermode();
}

void Void(void) {
    List list;
    Read(&list);
    list.table.s = list.tableCount.s;
    list.table.m = list.tableCount.m;
    list.table.l = list.tableCount.l;
    Save(list);
}

void Read(List *list) {
    FILE *fp;
    fp = fopen("/Users/jinjianxia/Public/store.txt", "r");
    //store.txt 记录菜品信息
    if (!fp) {
        printf("菜品文件打开失败！\n");
        exit(0);
    } else {
        list->length = 0;
        while (!feof(fp)) {
            fscanf(fp, "%s%s%d%d\n", list->data[list->length].number, list->data[list->length].name,
                   &(list->data[list->length].price), &(list->data[list->length].count));
            list->length++;
        }/* 先后录入编号、菜名、价格、单品数量 */
    }
    fclose(fp);
    FILE *fp1;
    fp1 = fopen("/Users/jinjianxia/Public/table.txt", "r");
    //table.txt 记录餐桌信息
    if (!fp1) {
        printf("餐桌文件打开失败！\n");
        exit(0);
    } else {
        while (!feof(fp1)) {
            fscanf(fp1, "%d%d%d", &(list->table.s), &(list->table.m), &(list->table.l));
        }/* 先后录入 s,m,l 型号桌子的数量 */
    }
    fclose(fp1);
    FILE *fp2;
    fp2 = fopen("/Users/jinjianxia/Public/tablecount.txt", "r");
    if (!fp2) {
        printf("餐桌数量文件打开失败！\n");
        exit(0);
    } else {
        while (!feof(fp2)) {
            fscanf(fp2, "%d%d%d", &(list->tableCount.s), &(list->tableCount.m), &(list->tableCount.l));
        }
    }
    fclose(fp2);
}

void Save(List list) {
    FILE *fp;
    fp = fopen("/Users/jinjianxia/Public/store.txt", "w");
    for (int i = 0; i < list.length; ++i) {
        fprintf(fp, "%s %s %d %d\n", list.data[i].number, list.data[i].name, list.data[i].price, list.data[i].count);
    }
    fclose(fp);
    FILE *fp1;
    fp1 = fopen("/Users/jinjianxia/Public/table.txt", "w");
    fprintf(fp1, "%d %d %d\n", list.table.s, list.table.m, list.table.l);
    fclose(fp1);
    FILE *fp2;
    fp2 = fopen("/Users/jinjianxia/Public/tablecount.txt", "w");
    fprintf(fp1, "%d %d %d\n", list.tableCount.s, list.tableCount.m, list.tableCount.l);
    fclose(fp2);
}
