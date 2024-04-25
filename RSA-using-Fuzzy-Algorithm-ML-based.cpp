/*
 FLUFFY RSA ALGORITHM IN C++
*/
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<string>
#include<cmath>
#include<cstdlib>
#include<time.h>


using namespace std;

/* Global declarations */

long int p_prime, q_prime, n, e_totient, i, spotted;
long int e_values[100], d_values[100];
long int temporary[100];
long int decrypted[100], encrypted[100];
long int Sqr;
int ENCRYPT[100], DECRYPT[100];
double t;

char plain_text[100] = { 0 };
char alphabets[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

/* fuzzy groups fot t-0.7 */
// only 26, even - 0, odd 

double mem_group[3] = { 0.7,0.5,0.4 };
double v_group[3] = { 0.3,0.4,0.5 };

/* fuzzy groups fot t-0.6 */
// only 26, even - 0, odd 

double mem_group1[3] = { 0.6,0.5,0.4 };
double v_group1[3] = { 0.3,0.4,0.5 };

int size_FN;

/* function to associate number to char */
int get_index(char x)
{
    for (int i = 0; i < 26; i++) {
        if (alphabets[i] == x or alphabets[i] - 32 == x)
        {
            return i;
        }
    }
    return 30;
}

/* function to get intuitionistic fuzzy number */
int* get_tIFN(char pt[])
{
    srand(time(0));
    int numerical[100];
    int size = 0;
    for (int i = 0; pt[i] != '\0'; i++)
    {
        numerical[i] = get_index(pt[i]) + 1;
        //cout << get_index(pt[i]) + 1 << endl;
        size++;
    }

    const int x = size * 5;
    int* tIFN = new int[x];
    int mem, v;
    int m, a, b;
    int iterat = 0;
    for (int i = 0; i < x; i++)
    {
        tIFN[i] = 0;
    }
    for (int j = 0; j < size; j++)
    {
        if (numerical[j] == 26)
        {
            mem = mem_group[0];
            v = v_group[0];
            m = rand() % (2 - 0 + 1);
            a = rand() % (2 - 0 + 1);
            b = numerical[j];
        }
        else if (numerical[j] % 2 == 0 and numerical[j] != 0) {
            mem = mem_group[1];
            v = v_group[1];
            m = rand() % (2 - 0 + 1);
            a = rand() % (2 - 0 + 1);
            b = numerical[j];
        }
        else if (numerical[j] % 2 == 1) {
            mem = mem_group[2];
            v = v_group[2];
            m = rand() % (2 - 0 + 1);
            a = rand() % (2 - 0 + 1);
            b = numerical[j];
        }
        else {
            m = 0;
            a = 0;
            b = numerical[j];
        }
        //------------------------------
        tIFN[j * 5] = m;//05
        tIFN[j * 5 + 1] = a;//16
        tIFN[j * 5 + 2] = b;//27
        tIFN[j * 5 + 3] = a;//38
        tIFN[j * 5 + 4] = b + 1;//49


    }

    cout << t <<" - INTUIONISTIC FUZZY NUMBER" << endl;
    cout << "[ [";
    for (int i = 0; i < size; i++)
    {

        for (int j = 0; j < 5; j++)
        {
            if ((j + 1) % 5 == 0 and j != 0)
            {
                cout << tIFN[i * 5 + j] << "] , [";
            }
            else if (j % 2 == 0 and j != 0) {
                cout << tIFN[i * 5 + j] << ": ";
            }
            else
            {
                cout << tIFN[i * 5 + j] << ", ";
            }
        }


    }
    cout << "]" << endl;
    size_FN = x;
    return tIFN;


}

/* function to get triangular Intuitionistic fuzzy number */
int* tri_tIFN(char a[])
{
    // cout << sizeof(FN[0])<< endl;
     //char a[] = "abx";
    int* IFuzz = get_tIFN(a);
    int* ttFN = new int[size_FN];
    for (int i = 0; i < size_FN; i++)
    {
        ttFN[i] = 0;
    }
    //cout << size_FN << endl;

    for (int x = 0; x < size_FN; x++)
    {
        ttFN[x] = IFuzz[x];
    }
    for (int i = 0; i < size_FN / 5; i++)
    {
        for (int j = 0; j < 5; j++) {
            if (j != 3 and (j + 1) % 2 == 0 and j != 0)
            {
                ttFN[i * 5 + j] = IFuzz[i * 5 + j] - 1;
            }
            else if ((j + 1) % 3 == 0 and j != 0)
            {
                ttFN[i * 5 + j] = IFuzz[i * 5 + j] - 1;
            }
        }
    }
    cout << "\n====================================================================================================================\n";
    cout << "TRIANGULAR " << t <<" - INTUITIONISTIC FUZZY NUMBER" << endl;
    cout << "<";
    for (int i = 0; i < size_FN / 5; i++)
    {

        for (int j = 0; j < 5; j++)
        {
            if ((j + 1) % 5 == 0 and j != 0)
            {
                cout << ttFN[i * 5 + j] << ">  <";
            }
            else if (j % 2 == 0 and j != 0) {
                cout << ttFN[i * 5 + j] << ": ";
            }
            else
            {
                cout << ttFN[i * 5 + j] << ", ";
            }
        }


    }
    cout << endl;
    cout << "\n====================================================================================================================\n";
    cout << endl;
    return ttFN;

}

/* function to convert to hex */
void ToHexa(int n)
{
    char hexaDecimal[100];
    int i = 0;
    while (n != 0) {
        int temp = 0;
        temp = n % 16;
        if (temp < 10) {
            hexaDecimal[i] = temp + 48;
            i++;
        }
        else {
            hexaDecimal[i] = temp + 55;
            i++;
        }
        n = n / 16;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        cout << hexaDecimal[j];
    }

}


/* function to check is it prime or not */
int prime_num(long int num) {
    int x;
    Sqr = sqrt(num);
    for (x = 2; x <= Sqr; x++)
    {
        if (num % x == 0)
            return 0;
    }
    return 1;

}

/* 26 SUGROUPS GENERATION */


/* function to generate e values */
/* co-prime check mandatory*/

long int generate_d(long int e_val);
void generate_e()
{
    int iterator = 0;
    iterator = 0;
    for (i = 2; i < e_totient; i++)
    {
        if (e_totient % i == 0)
            continue;
        spotted = prime_num(i);
        if (spotted == 1 && i != p_prime && i != q_prime)
        {
            e_values[iterator] = i;
            spotted = generate_d(e_values[iterator]);
            if (spotted > 0)
            {
                d_values[iterator] = spotted;
                iterator++;
            }
            if (iterator == 99)
                break;
        }
    }

}

/* function to generate possible d values */
long int generate_d(long int e_val)
{
    long int  val = 1;
    while (true)
    {
        val = val + e_totient;
        if (val % e_val == 0)
            return (val / e_val);
    }
}

/* Function to perform encryption */
void encryption()
{
    long int numerical, character, key = e_values[0], len;
    long int public_key1;
    i = 0;
    len = strlen(plain_text);
    while (i != len)
    {
        /* convert message to number */
        numerical = decrypted[i];
        numerical = numerical - 96;

        /* Encryption m^e mod n*/
        public_key1 = 1;
        for (Sqr = 0; Sqr < key; Sqr++)
        {
            public_key1 = public_key1 * numerical;
            public_key1 = public_key1 % n;
        }
        temporary[i] = public_key1;

        /* covert back to character */
        character = public_key1 + 96;
        encrypted[i] = character;
        i++;
    }
    encrypted[i] = -1;

    cout << "\nTHE ENCRYPTED MESSAGE IS: " << endl;
    for (i = 0; encrypted[i] != -1; i++)
    {
        printf("%c", encrypted[i]);
    }

    cout << endl << endl;
}

/* Function to perform decryption */
void decryption()
{
    long int dec_character, encryp_character, key = d_values[0];
    long int cipher;
    i = 0;
    while (encrypted[i] != -1)
    {
        encryp_character = temporary[i];

        cipher = 1;

        for (Sqr = 0; Sqr < key; Sqr++)

        {

            cipher = cipher * encryp_character;
            cipher = cipher % n;

        }

        dec_character = cipher + 96;

        decrypted[i] = dec_character;

        i++;
    }
    decrypted[i] = -1;

    cout << "\nTHE DECRYPTED MESSAGE IS: " << endl;
    for (i = 0; decrypted[i] != -1; i++)
    {
        printf("%c", decrypted[i]);
    }

    cout << endl << endl;

}

/* Main Function of RSA */

/* function to perform fuzzy encryption */
void Encrypt(char a[])
{
    int e = e_values[1];
    //int* ENCRYPT = new int[size_FN];
    int* triangular_FN = tri_tIFN(a);
    int m;
    int me, eme_1, eme_1_char;
    for (int i = 0; i < size_FN; i++)
    {
        ENCRYPT[i] = 0;
    }
    for (int i = 0; i < size_FN / 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j == 0)
            {
                m = triangular_FN[i * 5 + j];
                if (m == 0)
                {
                    break;
                }
                me = pow(m, e);
                // cout << "m0\t" << m << "m^e\t" << me % n << endl;
                ENCRYPT[i * 5 + j] = me % n;//-----------take mod

            }
            else
            {
                eme_1 = e * pow(m, e - 1);
                eme_1_char = eme_1 * triangular_FN[i * 5 + j];
                // cout << "m1\t" << m << "e*m^e-1\t" << eme_1 << "e*m^e-1*[]\t" << eme_1_char % n << endl;
                ENCRYPT[i * 5 + j] = eme_1_char % n;//-----------take mod

            }
        }
    }

    cout << "ENCRYPTED TRIANGULAR " << t << " INTUIONISTIC FUZZY NUMBER" << endl;
    cout << "<";
    for (int i = 0; i < size_FN / 5; i++)
    {

        for (int j = 0; j < 5; j++)
        {
            if ((j + 1) % 5 == 0 and j != 0)
            {
                cout << ENCRYPT[i * 5 + j] << ">  <";
            }
            else if (j % 2 == 0 and j != 0) {
                cout << ENCRYPT[i * 5 + j] << ": ";
            }
            else
            {
                cout << ENCRYPT[i * 5 + j] << ", ";
            }
        }


    }
    cout << endl;
   

}

/* function to perform fuzzy decryption */

void Decrypt(int* enc)
{
    int d = d_values[1];
    int m;
    int md, dmd_1, dmd_1_char;
    for (int i = 0; i < size_FN; i++)
    {
        DECRYPT[i] = enc[i];
    }
    for (int i = 0; i < size_FN / 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j == 0)
            {
                m = enc[i * 5 + j];
                /* if (m == 0)
                 {
                     break;
                 }*/
                md = pow(m, d);
                // cout << "m0\t" << m << "m^e\t" << me % n << endl;
                DECRYPT[i * 5 + j] = md % n;//-----------take mod

            }
            else
            {
                dmd_1 = d * pow(m, d - 1);
                dmd_1_char = dmd_1 * enc[i * 5 + j];
                // cout << "m1\t" << m << "e*m^e-1\t" << eme_1 << "e*m^e-1*[]\t" << eme_1_char % n << endl;
                DECRYPT[i * 5 + j] = dmd_1_char % n;//-----------take mod

            }
        }
    }

    for (int i = 0; i < size_FN / 5; i++) {
        for (int j = 0; j < 5; j++) {
            if ((j + 1) % 5 == 0 and j != 0)
            {
                cout << DECRYPT[(i * 5) + j] << "> <";
            }
            else if (j != 0 and j % 2 == 0) {
                cout << DECRYPT[(i * 5) + j] << ": ";
            }
            else
            {
                cout << DECRYPT[(i * 5) + j] << ",";
            }
        }
    }
    cout << endl;

}
/* function to get plain_text */
void back_to_text(char *pt)
{
    cout << "\n====================================================================================================================\n";
    int* tri = get_tIFN(pt);
    int plain[100];
    int index = 0;
    cout << "\n====================================================================================================================\n";
    for (int i = 0; i < size_FN / 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if ((j + 1) % 5 == 0 and j != 0)
            {
                //cout << tri[i * 5 + j] << ">  <";
            }
            else if (j % 2 == 0 and j != 0) {
                //cout << tri[i * 5 + j] << ": ";
                plain[index] = tri[(i * 5) + j];
                index++;
            }
            else
            {
                //cout << tri[i * 5 + j] << ", ";
            }
           
 
        }
    }
    cout<<"PLAIN TEXT GENERATION:"<<endl;
    for (int k = 0; k < size_FN/5; k++)
    {
        if (plain[k] - 1 < 26)
        {
            cout << alphabets[plain[k]-1] << " ";
        }
        else
        {
            cout << " ";
        }
        
    }
    cout << endl;
}
int main()
{
    
    cout << "select t, 0.6 or 0.7" << endl;
    cin >> t;
    cout << "\n====================================================================================================================\n";
    cout << "\nENTER FIRST PRIME NUMBER\n";
    cin >> p_prime;
    cout << endl;
    spotted = prime_num(p_prime);
    if (spotted == 0)
    {
        cout << "\nWRONG INPUT\n";
        exit(1);
    }
    cout << "\nENTER ANOTHER PRIME NUMBER\n";
    cin >> q_prime;
    spotted = prime_num(q_prime);
    if (spotted == 0 || p_prime == q_prime)
    {
        cout << "\nWRONG INPUT\n";
        exit(1);
    }

    cout << "\n====================================================================================================================\n";
    cout << "\n------NOW WE ARE READY TO START THE ENCRYPTION DECRYPTION PROCESS------\n";

    cout << "\nENTER MESSAGE TO BE ENCRYPTED\n";
    fflush(stdin);
    //cin.ignore();
    cin.getline(plain_text, 100);

    cout << "\n====================================================================================================================\n";

    for (i = 0; plain_text[i] != '\0'; i++)
        decrypted[i] = plain_text[i];
    n = p_prime * q_prime;
    e_totient = (p_prime - 1) * (q_prime - 1);

    generate_e();
    cout << "\nPOSSIBLE VALUES OF e AND d ARE\n";
    for (i = 0; i < Sqr - 1; i++)
    {
        cout << e_values[i] << "\t" << d_values[i] << "\n";
    }
    cout << "\n====================================================================================================================\n";

    cout << endl << "PRIVATE AND PUBLIC KEY PAIR" << endl;
    cout << endl << "PUBLIC KEY: (" << n << " , " << e_values[0] << ")" << endl;
    cout << endl << "PRIVATE KEY: " << d_values[0] << endl;

    double Uat[3];
    double Vat[3];
    //Uat
    double p = min(t, mem_group[0]);//min(l,t)
    double q = min(t, mem_group[1]);//min(m,t)
    double r = min(t, mem_group[2]);//min(n,t)

   //Vat
    double P = max(1-t, v_group[0]);//max(L,1-t)
    double Q = max(1 - t, v_group[1]);//max(M,1-t)
    double R = max(1 - t, v_group[2]);//max(N,1-t)

    Uat[0] = p;
    Uat[1] = q;
    Uat[2] = r;

    Vat[0] = P;
    Vat[1] = Q;
    Vat[2] = R;

    double rho, eta;
    rho = min(p, q);
    rho = min(rho, r);
    eta = max(P, Q);
    eta = max(eta, R);



    cout << "\n====================================================================================================================\n";
    cout << "(RHO,ETA)- LEVEL SUBGROUPS CALCULATION " << endl;
    cout << "rho:" << rho << "\teta: " << eta << endl;
    //encryption();

   


    //decryption();
    cout << "\n====================================================================================================================\n";

    char a[] = "abx";
    //get_tIFN(a);
    //tri_tIFN(a);
    Encrypt(plain_text);
    cout << "\n====================================================================================================================\n";
    cout << "DECRYPTED TRIANGULAR " << t << " INTUIONISTIC FUZZY NUMBER" << endl;
    cout << "<";
    Decrypt(ENCRYPT);
    cout << "\n====================================================================================================================\n";
    
    back_to_text(plain_text);
    return 0;
}

