#include <iostream>
#include <vector>
#include <fstream>

#define HASH_TABLE_SIZE 2000
#define MODULO_VALUE 2000
#define HASH_BASE 31

using namespace std;

typedef struct{
    string name ;
    string profit_tax ;
    string address;
}Company;

typedef struct{
    vector<Company> table;
}HashTable;

vector<Company> readCompanyList(string file_name)
{
    ifstream input_file(file_name);
    vector<Company> company_info;
    if (input_file.is_open())
    {
        string line;
        string tmp_name_cpn;
        string tmp_tax_id;
        string tmp_addres;
        Company tmp_cpn;
        while (getline(input_file,line))
        {
        /*
            TEN_CTY|MST<number>|DIA_CHI_CTY
        */
            size_t first_delim=line.find('|');
            (tmp_cpn.name).assign(line.begin(),line.begin()+first_delim);

            size_t second_delim= line.find('|',first_delim+1);
            (tmp_cpn.profit_tax).assign(line.begin()+first_delim+1,
                line.begin()+second_delim);

            (tmp_cpn.address).assign(line.begin()+second_delim+1,line.end());
            
            company_info.push_back(tmp_cpn);
        }
    }

    //Xóa thông tin các cột (dòng đầu tiên)
    company_info.erase(company_info.begin());

    input_file.close();
    return company_info;
}

//Sử dụng lũy thừa nhị phân kết hợp modulo
// ((a)^b)%m = (a%m*..<b lần>..*a%m)%m
long long binaryPowerModN(long long a,long long b,long long n)
{
    if (b==0) return 1;
    long long result = 1;
    while (b>0){
        //b&1 <=> b%2
        if (b&1)
        {
             result = (result * a) % n;
        }
        a = (a*a)%n;
        b>>=1;//<=> b/=2
    }
    return result;
}

long long hashString(string company_name){
    size_t name_len = company_name.length();
    long long hash = 0;
    size_t start = (name_len<20)?0:name_len-21;
    for (int i = start;i<name_len;i++)
    {
        //(a+b)%m = (a%m+b%m)%m
        hash += (company_name[i]*binaryPowerModN(HASH_BASE,i,MODULO_VALUE))%MODULO_VALUE;
        hash%=MODULO_VALUE;
    }
    return hash;    
}

//kiểm tra xem c này đã được gán giá trị hợp lệ chưa
bool isExist(Company c)
{ 
    if (c.name==""&&c.address==""&&c.profit_tax=="") return false;
    return true;
}

HashTable* createHashTable(vector<Company> list_company)
{
    HashTable* mHashTable = new HashTable;
    //gán lại bảng băm với toàn bộ phần tử là giá trị rỗng
    vector<Company> c(HASH_TABLE_SIZE,{"","",""});
    (mHashTable->table).assign(c.begin(),c.end());
    for (Company x:list_company)
    {
        //Xử lý va chạm bằng linear probing
        long long hash = hashString(x.name);
        while (isExist(mHashTable->table[hash]))
        {
            hash++; 
        }
        mHashTable->table[hash] = x;
    }
    return mHashTable;
}

Company* search(HashTable* hash_table, string company_name)
{
    long long hash = hashString(company_name);
    long long index = hash;
    while(isExist(hash_table->table[index]))
    {
        if (hash_table->table[index].name==company_name)
        {
            Company *res = new Company;
            *res = hash_table->table[index];
            return res;
        }
        index++;
        index%=HASH_TABLE_SIZE;//Giữ index luôn hợp lệ
        if (index==hash)
            break;
    }
        return nullptr;
}

void insert(HashTable* hash_table, Company company)
{
    //đã tồn tại công ty này
    if (search(hash_table,company.name)!=nullptr)
    {
        return;
    }
    long long hash = hashString(company.name);
    long long index = hash;
    while (!isExist(company))
    {
        index++;
    }
    hash_table->table[index] = company;
}

int main(int argc, char*argv[])
{
    vector<Company> mst = readCompanyList(argv[1]);
    HashTable*hash_table = createHashTable(mst);

    ifstream input(argv[2]);
    ofstream output(argv[3]);
    
    
    string line;

    while(getline(input,line))
    {
        Company*c = search(hash_table,line);
        if(c!=nullptr)
        {
            output<<c->name<<"|"<<c->profit_tax<<"|"<<c->address<<endl;
            
        }
    }

    input.close();
    output.close();
    return 0;
}