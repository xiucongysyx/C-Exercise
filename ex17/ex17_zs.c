#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> //头文件

#define MAX_DATA 512 //名字数组和邮箱数组的长度
#define MAX_ROWS 100 //数据量，即能够存储几组数据

struct Address { //结构体address，该结构体存储了每组数据的具体内容
    int id;     //数据id
    int set;    //数据是否储存了数据
    char name[MAX_DATA]; //名字
    char email[MAX_DATA];//邮箱
};

struct Database { //结构体Database，该结构体是嵌套结构体，他包含了MAX_ROWS 个address。
    struct Address rows[MAX_ROWS]; //我们可以使用Database->rows[i] 来访问指定的address结构体。
};

struct Connection { //结构体Connection，该结构体包含了一个文件名的指针和一个Database 结构体的指针
    FILE *file;
    struct Database *db;
};

void die(const char *message) //die函数，用来打印错误信息，主要是一些可以通过编译，但是实际上不满足我们设计要求的错误。
{
    if(errno) { //通过errno参数来判断是否操作系统也检测到了错误。
        perror(message); //如果是的话，使用perror函数打印对应的信息。
    } else {
        printf("ERROR: %s\n", message); //如果操作系统没有报错的话，就打印我们传递的信息。
    }

    exit(1); //然后退出程序。
}

void Address_print(struct Address *addr) //这个函数用来打印address 类型的结构体中的内容。
{
    printf("%d %s %s\n", //这个函数的参数是一个address类型结构体的指针，因此我们可以使用->来打印其中的内容
            addr->id,addr->name,addr->email);
}

void Database_load(struct Connection *conn) //这个函数用来将文件的内容加载到Database 结构体中。
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file); //fread从文件中读取内容存放到数据库中，读取到conn的db中，元素大小是Database 类型结构体的大小，读取一个元素，文件的名字。
    if(rc != 1) die("Filed to load database."); //如果读出来是空的话，或者没有该文件，使用die返回报错信息。
}
struct Connection *Database_open(const char *filename, char mode) //创造一个Database 类型的数据库，并返回。
{
    struct Connection *conn = malloc(sizeof(struct Connection)); //使用malloc给结构体分配内存。
    if(!conn) die("Memory error"); //创造失败的话，打印错误。

    conn->db = malloc(sizeof(struct Database));i //给conn中的Database 类型的结构体分配内存，在conn中，db只是一个指针，因此需要再次给db分配空间。 
    if(!conn->db) die("Memory error"); //如果创造失败，打印错误信息并结束程序。

    if(mode == 'c') { //参数是c，就以写的模式获取文件指针。这里的c是create，当创造数据库时，使用写模式获取文件指针。
        conn->file = fopen(filename, "w");
    } else { //否则的话，使用只读的模式获取文件指针。
        conn->file = fopen(filename, "r+");

        if(conn->file) { //如果成功获取文件指针，就将文件中的数据加载到结构体中。
            Database_load(conn);
        }
    }

    if(!conn->file) die("Failed to open the file"); //如果没有获取到文件指针，就打印错误信息。

    return conn;
}

void Database_close(struct Connection *conn) //关闭结构体，释放malloc函数分配的内存空间。
{
    if(conn) {
        if(conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection *conn) //向数据库中写数据
{
    rewind(conn->file); //将文件的指针重新设置为开头的位置

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file); //将数据库db中的内容写入文件中。写入元素的长度为数据库的长度，写入的元素为一个。
    if(rc !=1) die("Failed to write database."); //rc 是写入函数的返回值，当成功写入是，返回为1。

    rc = fflush(conn->file); //这行代码的意思是将缓冲区的文件立即写入文件中，可以理解成保存文件。
    if(rc == -1) die("Cannot flush fatabase.");
}

void Database_create(struct Connection *conn) //创造数据库类型的结构体
{
    int i = 0;

    for(i = 0; i < MAX_ROWS; i++) {
        struct Address addr = {.id = i, .set = 0}; //创造MAX_ROWS 个address类型的结构体，并对id和set进行初始化。
        conn->db->rows[i] = addr; //具体的方法是创建一个address类型的结构体并完成初始化，并将其复制到conn->db->rows[i]中。
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email) //将数据存入结构体中
{
    struct Address *addr = &conn->db->rows[id]; //首先是通过id定位到确定的rows[id]，这一步将相当于给rows[i]取了一个别名。
    if(addr->set) die("Already set, delete it first"); //判断这块区域是否已经存有数据

    addr->set = 1; //将数据标志设置为1，表示这块区域已经有数据了。
    char *res = strncpy(addr->name, name, MAX_DATA); //将name和email通过strncpy赋值给数据库中。
    if(!res) die("Name copy failed");

    res = strncpy(addr->email, email, MAX_DATA);
    if(!res) die("Email copy failed");
}

void Database_get(struct Connection *conn, int id) //得到数据库，打印数据库中的内容
{
    struct Address *addr = &conn->db->rows[id]; //给rows[i]设置别名
    if(addr->set) {
        Address_print(addr); //如果这个id中有数据，就打印出数据内容
    } else {
        die("ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id) //删除数据库结构体，这个函数的目的是删除数据库文件中存的某一组数据
{
    struct Address addr = {.id = id, .set = 0}; //创造一个address类型的结构体，并将id和set初始化。
    conn->db->rows[id] = addr; //把它赋值给rows[i]
}

void Database_list(struct Connection *conn) //列出整个数据库文件中的内容
{
    int i = 0;
    struct Database *db = conn->db; //将db地址复制给该函数中的db。此处可以看到没有&符号，因为db本身就是地址，而rows[i]实际上是第一个值，因此需要使用&取地址后才能将地址赋给指针。

    for(i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[]) //主函数
{
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]"); //当输入参数不足3个时，报错。

    char *filename = argv[1]; //文件名是第二个参数
    char action = argv[2][0]; //行为，就是执行什么操作，是地三个参数的第一个字符，这样的话，输入get得到的指令时'g'。
    struct Connection *conn = Database_open(filename, action); //创造connection 类型的结构体
    int id = 0; //初始化id为0

    if(argc > 3) id = atoi(argv[3]); //若参数大于3个，则将第四个参数转换为int类型的数据。
    if(id >= MAX_ROWS) die("There's not that many records."); //如果id大于了可以储存的最大值，就报错

    switch(action) { //使用switch函数监控switch
        case 'c': //action 为 c 则执行创造数据库文件操作，创造一个数据库文件，正确的理解应该是初始化一个数据库文件。使可以从中寻找到id和对应的set的值。
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g': //get 一组数据的值，通过输入的id，获取对应组的数据的内容。
            if(argc != 4) die("Need an id to get");

            Database_get(conn, id);
            break;

        case 's': //set 一组数据的内容，这个操作需要6个参数，包括文件名，操作，id, name, email
            if(argc != 6) die("Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd': //delete 一组数据的内容。主要是删除name和email。
            if(argc != 4) die("weed id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l': //list 数据库所有的内容
            Database_list(conn);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list"); //默认，如果不是上面几种操作，就提示需要输入action。
    }

    Database_close(conn);

    return 0;
}
            

