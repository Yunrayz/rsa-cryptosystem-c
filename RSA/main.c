#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


/** @brief On a cr��e une structure pour pouvoir utiliser des tableaux dynamiques et les return avec des fonctions. On a ainsi l'adresse du tableau, l'indice le plus haut et le signe du nombre qu'elle contient.
 */
typedef struct
{
    int *tab;
    int len;
    int sign; /* 0 si positif, 1 si n�gatif*/
} numb;

/** @brief Cette structure sert uniquement dans l'algorithme d'Euclide �tendu, on peut ainsi return 3 numb � la fois.
 */
typedef struct
{
    numb r;
    numb u;
    numb v;
} res_eucl_et;

numb substract(numb, numb);



/** @brief Split est une fonction qui permet de convertir un int en numb. Elle divise le nombre par 10 � chaque it�ration, apr�s avoir r�cuper� le chiffre des unit�s et l'avoir mis dans le tableau
 *
 * @param Un entier.
 * @return Un numb.
 *
 */
numb split(int num)
{
    int *tab;
    int len;
    int temp;
    int i;
    numb res;

    /* On commence par regarder le signe de l'entier*/
    if (num < 0)
    {
        res.sign=1;
        num=-num;
    }
    else
    {
        res.sign=0;
    }


    len = 0;
    temp = num;

    while (temp>9)
    {
        len++;
        temp=temp/10;
    }

    tab = malloc(len+1 * sizeof (int));

    if (tab == NULL) // Si l'allocation a �chou�
    {
        exit(0); // On arr�te imm�diatement le programme
    }


    if (num < 10)
    {
        tab[0]=num;
    }
    else
    {
        for (i=0; i<len; i++)
        {
            tab[i]=num%10;
            num=num/10;
        }
    }

    tab[len]=num;
    res.tab=tab;
    res.len=len;

    return res;
}




/** @brief Cette fonction compare les valeurs absolues des deux numb entr�s.
 *
 * @param Un numb
 * @param Un autre numb
 * @return Un int : 1 si le premier est sup�rieur au deuxi�me, 2 s'ils sont �gaux et 0 si le deuxi�me est sup�rieur au premier.
 *
 */

int compare(numb p, numb q)
{
    /* res = 0 --> p < q
    res = 1 --> p > q
    res = 2 --> p = q*/

    int res;
    int i;

    if (p.len > q.len)
    {
        res=1;
    }
    else if (q.len > p.len)
    {
        res=0;
    }
    else
    {
        i = p.len;
        while (p.tab[i]==q.tab[i] && i>=0)
        {
            i--;
        }
        if (i < 0)
        {
            res = 2;
        }
        else if (p.tab[i]>q.tab[i])
        {
            res = 1;
        }
        else
        {
            res = 0;
        }
    }

    return res;
}



/** @brief Une fonction qui permet d'additionner deux numb, positifs ou n�gatifs. Elle �tudie d'abord les signes des deux numb avant de parcourir les tableaux pour additionner les nombres. On finit par v�rifier toutes les cases du tableaux. Si une case est sup�rieur � 10, on lui retranche 10 et on ajoute 1 � la case sup�rieure.
 *
 * @param Un numb p
 * @param Un autre numb q
 * @return Un numb res=p+q
 *
 */

numb add(numb p, numb q)
{
    numb res;
    int *tab;
    int *tab_res;
    int len;
    int ind_min;
    int i;
    int a=0;
    int p_bigger;

    if (p.sign == q. sign)
    {
        res.sign = p.sign;

        if (p.len>q.len)
        {
            len=p.len;
            ind_min=q.len;
            p_bigger=1;
        }
        else
        {
            len=q.len;
            ind_min=p.len;
            p_bigger=0;
        }


        tab = malloc(len+1 * sizeof (int));

        if (tab == NULL)
        {
            exit(0);
        }

        for (i=0; i<=ind_min; i++)
        {
            tab[i]=p.tab[i]+q.tab[i]+a;
            if (tab[i]>9)
            {
                a=1;
                tab[i]=tab[i]-10;
            }
            else
            {
                a=0;
            }
        }

        if (p_bigger==1)
        {
            for (i=ind_min+1; i<=len; i++)
            {
                tab[i]=p.tab[i]+a;
                a=0;

            }
        }
        else
        {
            for (i=ind_min+1; i<=len; i++)
            {
                tab[i]=q.tab[i]+a;
                a=0;

            }
        }



        if (tab[len]>10)
        {
            res.len=len+1;
            tab_res = malloc(res.len+1 * sizeof (int));
            if (tab_res == NULL)
            {
                exit(0);
            }
            for (i=0; i<=len; i++)
            {
                tab_res[i]=tab[i];
            }
            tab_res[len]=tab_res[len]-10;
            res.tab[res.len]=1;
        }
        else
        {
            res.len=len;
            tab_res = malloc(res.len+1 * sizeof (int));
            if (tab == NULL)
            {
                exit(0);
            }
            for (i=0; i<=len; i++)
            {
                tab_res[i]=tab[i];
            }
        }

        free(tab);
        res.tab=tab_res;
    }

    else if (p.sign == 0)
    {
        if (compare(p, q) == 1)
        {
            q.sign = 0;
            res = substract(p, q);
        }
        else
        {
            q.sign = 0;
            res = substract(q, p);
            res.sign = 1;
        }

    }
    else
    {
        if (compare(p, q) == 0)
        {
            p.sign = 0;
            q.sign = 0;
            res = substract(q, p);
        }
        else
        {
            p.sign = 0;
            q.sign = 0;
            res=substract(p, q);
            res.sign = 1;
        }
    }

    return res;
}



/** @brief Cette fonction permet de faire la diff�rence entre deux numb, sans cnsid�rer le signe. On part du principe que p et q sont positifs et que p>q. On ne l'utilisera jamais directement pour faire p-q. Elle sert principalement dans la fonction add.
 *
 * @param Un numb p
 * @param Un numb q
 * @return Un numb res=p-q
 *
 */

numb substract(numb p, numb q)
{
    /*on part directement du principe que p>q, il faudra y faire attention par la suite*/

    numb res;
    int *tab;
    int *tab_res;
    int i;
    int a=0;



    tab = malloc(p.len+1 * sizeof (int));

    if (tab == NULL)
    {
        exit(0);
    }

    for (i=0; i<=q.len; i++)
    {
        tab[i]=p.tab[i]-q.tab[i]-a;
        if (tab[i]<0)
        {
            a=1;
            tab[i]=tab[i]+10;
        }
        else
        {
            a=0;
        }
    }

    for (i=q.len+1; i<=p.len; i++)
        {
            tab[i]=p.tab[i]-a;
            a=0;
            if (tab[i]<0)
            {
                a=1;
                tab[i]=tab[i]+10;
            }
            else
            {
                a=0;
            }

        }

    i=p.len;
    while (tab[i]==0 && i>0)
    {
        i--;
    }

    res.len=i;
    tab_res = malloc(res.len+1 * sizeof (int));

    if (i == 0)
    {
        tab_res[0]=0;
    }
    else
    {
        for (i=0;i<=res.len;i++)
        {
           tab_res[i]=tab[i];
        }
    }




        free(tab);
        res.tab = tab_res;
        res.sign=0;
        return res;
}



/** @brief Voici la vrai fonction de soustraction. Elle �tudie le signes du deuxi�me numb avant d'appeler add en utilisant les bons signes.
 *
 * @param Un numb p
 * @param Un numb q
 * @return Un numb res=p-q
 *
 */

numb sub (numb p, numb q)
{
    if (q.sign == 0)
    {
        q.sign = 1;
    }
    else
    {
        q.sign = 0;
    }

    return add(p, q);
}



/** @brief Mult est la fonction qui sert � multiplier deux numb. On parcourt chiffre par chiffre p, en multipliant chiffre par chiffre q, et en ajoutant le r�sultat dans le tableau res � la bonne place. On proc�de ensuite � une v�rification et une correction au cas o� certaines cases contiennent des int plus grand que 9.
 *
 * @param Un numb p
 * @param Un numb q
 * @return Un numb res=p*q
 *
 */

numb mult(numb p, numb q)
{
    numb res;
    int *tab;
    int i;
    int j;

    tab = calloc((p.len+q.len+2), sizeof (int));

    if (tab == NULL)
    {
        exit(0);
    }

    for (i=0; i<=p.len; i++)
    {
        for (j=0; j<=q.len; j++)
        {

            tab[i+j]=tab[i+j]+q.tab[i]*p.tab[j];

        }
    }

    for (i=0;i<=p.len+q.len; i++)
    {
        if (tab[i]>9)
        {
            tab[i+1]=tab[i+1]+tab[i]/10;
            tab[i]=tab[i]%10;
        }
    }

    if (tab[p.len+q.len+1]==0)
    {
        res.len = p.len+q.len;
        res.tab = malloc((res.len+1) * sizeof (int));
        for (i=0;i<=res.len; i++)
        {
            res.tab[i]=tab[i];
        }
    }
    else
    {
        res.len=p.len+q.len+1;
        res.tab = malloc((res.len+1) * sizeof (int));
        for (i=0;i<=res.len; i++)
        {
            res.tab[i]=tab[i];
        }
    }

    if (p.sign == 0)
    {
        if (q.sign == 0)
        {
            res.sign = 0;
        }
        else
        {
            res.sign = 1;
        }
    }
    else
    {
        if (q.sign == 0)
        {
            res.sign = 1;
        }
        else
        {
            res.sign = 0;
        }
    }


    return res;
}



/** @brief Une fonction puisance r�cursive qui utilise la fonction mult.
 *
 * @param Un numb p
 * @param Un int n
 * @return Un numb res=p^n
 *
 */

numb puissance(numb p, int n)
{
    numb res;
    if (n==1)
    {
        res=p;

    }
    else if (n%2==0)
    {
        res=puissance(mult(p, p), n/2);
    }
    else
    {
        res=mult(p, puissance(mult(p, p), ((n-1)/2)));
    }

    if (p.sign == 0)
    {
        res.sign = 0;
    }
    else if (n%2 == 0)
    {
        res.sign = 0;

    }
    else
    {
        res.sign = 1;
    }

    return res;
}



/** @brief Une fonction qui renvoie le reste de la division euclidienne de pp par q.
 *
 * @param Un numb p
 * @param Un numb q
 * @return Le reste de p/q
 *
 */

numb modulo(numb p, numb q)
{
    numb res;
    int i;

    if (q.len==0 && q.tab[0]==1)
    {
        res.len=0;
        res.tab = malloc(1 * sizeof (int));
        if (res.tab == NULL)
        {
            exit(0);
        }
        res.tab[0]=0;
    }
    else
    {
        res = sub(p, q);

        while (res.len>q.len)
        {
            res = sub(res, q);
        }


        while (res.len==q.len && res.tab[res.len]>q.tab[q.len])
        {
            res = sub(res, q);

        }


        i=res.len;

        while (res.tab[i] == q.tab[i] && i>=0)
        {
            i--;
        }

        if (i == -1)
        {
            res = sub(res, q);

        }
    }

    res.sign = 0;

    return res;
}



/** @brief Une fonction pgcd qui utilise modulo.
 *
 * @param Un numb p
 * @param Un numb q
 * @return Un numb res = p mod[q]
 *
 */

numb pgcd(numb p, numb q)
{
    numb r;

    r=modulo(p, q);
    if (r.len != 0 || r.tab[0] != 0)
    {
        pgcd(q, r);
    }
    else
    {
        return q;
    }
}



/** @brief L'algorthme d'Euclide �tendu, il permet de d�terminer les coefficients de B�zout lorsque pgcd(a,b)=1
 *
 * @param Un numb a
 * @param Un numb b
 * @return Une structure contenant u, v et le reste de la division euclidienne de a par b (normalement toujours 1)
 *
 */

res_eucl_et eucl_et(numb a, numb b)
{
    res_eucl_et res;
    numb r;
    numb r_;
    numb u;
    numb u_;
    numb v;
    numb v_;
    numb q;
    numb rs;
    numb us;
    numb vs;

    r = a;
    r_ = b;
    u = split(1);
    v = split(0);
    u_ = split(0);
    v_ = split(1);

    while (r_.len != 0 && r_.tab[0] != 0)
    {
        q = modulo(r, r_);
        rs = r;
        us = u;
        vs = v;
        r = r_;
        u = u_;
        v = v_;
        r_ = sub(rs, mult(q, r_));
        u_ = sub(us, mult(q, u_));
        v_ = sub(vs, mult(q, v_));
    }

    res.r=r;
    res.u=u;
    res.v=v;

    return res;
}



/** @brief La retranscription de l'algorithme qui permet de g�n�rer (e, n) et d les clefs priv�e et publiques.
 *
 */

void generate_key()
{
    unsigned long p_int;
    unsigned long q_int;
    unsigned long phi_int;
    int i;
    int found;
    int rand_int;
    char c;
    numb p;
    numb q;
    numb n;
    numb phi;
    numb e;
    numb d;
    numb test_mod;
    numb test_pgcd;
    res_eucl_et eucl;
    FILE* e_bin = NULL;
    FILE* e_len = NULL;
    FILE* e_sign = NULL;
    FILE* n_bin = NULL;
    FILE* n_len = NULL;
    FILE* n_sign = NULL;
    FILE* d_bin = NULL;
    FILE* d_len = NULL;
    FILE* d_sign = NULL;






    printf("Entrez un premier grand nombre entier :\n");
    scanf("%d",&p_int);
    p=split(p_int);

    printf("Entrez un deuxieme grand nombre entier :\n");
    scanf("%d",&q_int);
    q=split(q_int);

    n=mult(p, q);

    p=sub(p, split(1));
    q=sub(q, split(1));

    phi=mult(p, q);
    phi_int=p_int*q_int;

    srand(time(NULL));
    found = 0;
    while(found == 0)
    {
        rand_int=rand()%phi_int;
        printf("rand_int = %d", rand_int);
        e = split(rand_int);
        printf("random ");
        test_mod = modulo(phi, e);
        printf("test modulo ");
        if (test_mod.len != 0 || test_mod.tab[0] != 0)
        {
            printf("Calcul de pgcd...\n");
            test_pgcd = pgcd(phi, e);
            if (test_pgcd.len == 0 && test_pgcd.tab[0] == 1)
            {
                found = 1;
                printf("Found !\n");
            }
        }
    }

    eucl = eucl_et(e, phi);
    d=eucl.u;

    e_bin = fopen("Clef publique/e.bin", "wb");
    e_len = fopen("Clef publique/e.len", "wb");
    e_sign = fopen("Clef publique/e.sign", "wb");

    n_bin = fopen("Clef publique/n.bin", "wb");
    n_len = fopen("Clef publique/n.len", "wb");
    n_sign = fopen("Clef publique/n.sign", "wb");


    d_bin = fopen("Clef privee/d.bin", "wb");
    d_len = fopen("Clef privee/d.len", "wb");
    d_sign = fopen("Clef privee/d.sign", "wb");




    printf("Fichiers ouverts");




    fwrite(d.tab , sizeof(int) , d.len+1 , d_bin);
    fwrite(d.len , sizeof(int) , 1 , d_len);
    fwrite(d.sign , sizeof(int) , 1 , d_sign);
    fclose(d_len);
    fclose(d_bin);
    fclose(d_sign);

    printf("Ecriture clef privee");



    fwrite(e.tab , sizeof(int) , e.len+1 , e_bin);
    fwrite(e.len , sizeof(int) , 1 , e_len);
    fwrite(e.sign , sizeof(int) , 1 , e_sign);
    fclose(e_bin);
    fclose(e_len);
    fclose(e_sign);

    fwrite(n.tab , sizeof(int) , n.len+1 , n_bin);
    fwrite(n.len , sizeof(int) , 1 , n_len);
    fwrite(n.sign , sizeof(int) , 1 , n_sign);
    fclose(n_bin);
    fclose(n_len);
    fclose(n_sign);

    printf("Ecriture clef publique");

}



/** @brief ce programme permet de lire un fichier contenant un entier.
 *
 * @param Le fichier
 * @return L'entier
 *
 */

int read_int(FILE* fichier)
{
    int res;

    fread( &res , sizeof(int) , 1 , fichier );

    return res;
}



/** @brief De m�me cette fonction permet de lire un fichier contenant un tableau d'entier.
 *
 * @param Le fichier
 * @return Le tableau d'entier.
 *
 */

int * read_tab(FILE* fichier, int n)
{
    int * res;

    res = malloc(n * sizeof(int));

    fread(res, sizeof(int), n, fichier );

    return res;
}



/** @brief De m�me cette fonction permet de lire un fichier contenant une cha�ne de caract�re.
 *
 * @param Le fichier
 * @param La clef n
 * @return La cha�ne de caract�re.
 *
 */

char * read_message(FILE* fichier, int n)
{
    int log_bin;
    int i;
    int i_start;
    char * string;
    char c;

    log_bin=floor(log(n)/log(2));
    string = malloc(log_bin+2 * sizeof(char));

    i_start=0;
    c=getc(fichier);
    while (c!='EOF' && i_start<=log_bin)
    {
        i_start++;
        string[i_start]=c;
        c=getc(fichier);
    }

    for (i=i_start; i<=log_bin; i++)
    {
        string[i]=0;
    }

    string[log_bin+1]='\0';

    return string;
}



/** @brief La fonction qui permet de chiffrer un message dans un fichier.
 *
 */

void chiffrer()
{
    FILE * fichier;
    FILE * fichier_chif;
    FILE* e_bin = NULL;
    FILE* e_len = NULL;
    FILE* e_sign = NULL;
    FILE* n_bin = NULL;
    FILE* n_len = NULL;
    FILE* n_sign = NULL;
    FILE* mes_bin = NULL;
    FILE* mes_len = NULL;
    FILE* mes_sign = NULL;
    numb e;
    int e_int;
    numb n;
    int n_int;
    int i;
    char * chemin;
    int message;
    numb message_numb;
    numb res;

    e_bin = fopen("Clef publique/e.bin", "rb");
    e_len = fopen("Clef publique/e.len", "rb");
    e_sign = fopen("Clef publique/e.sign", "rb");

    n_bin = fopen("Clef publique/n.bin", "rb");
    n_len = fopen("Clef publique/n.len", "rb");
    n_sign = fopen("Clef publique/n.sign", "rb");

    e.sign=read_int(e_sign);
    e.len=read_int(e.len);
    e.tab=read_tab(e_bin, e.len);
    fclose(e_bin);
    fclose(e_len);
    fclose(e_bin);

    n.sign=read_int(n_sign);
    n.len=read_int(n.len);
    n.tab=read_tab(n_bin, n.len);
    fclose(n_bin);
    fclose(n_len);
    fclose(n_bin);

    printf("Entrez le chemin et nom du fichier a chiffrer");
    scanf("%s", chemin);

    fichier = fopen(chemin, "rb");

    n_int=0;
    for (i=0; i<=n.len; i++)
    {
        n_int=n_int+pow(10,i)*n.tab[i];
    }
    message=read_message(fichier, n_int);
    message_numb=split(message);
    fclose(fichier);

    e_int=0;
    for (i=0; i<=n.len; i++)
    {
        e_int=e_int+pow(10,i)*e.tab[i];
    }
    res=modulo(puissance(message_numb, e_int), n);


    mes_bin = fopen("message chiffre/message.bin", "wb");
    mes_len = fopen("message chiffre/message.len", "wb");
    mes_sign = fopen("message chiffre/message.sign", "wb");

    fwrite(message_numb.tab , sizeof(int) , message_numb.len+1 , mes_bin);
    fwrite(message_numb.len , sizeof(int) , 1 , mes_len);
    fwrite(message_numb.sign , sizeof(int) , 1 , mes_sign);
    fclose(mes_bin);
    fclose(mes_len);
    fclose(mes_sign);

}



/** @brief La fonction qui permet de d�chiffrer un message dans un fichier.
 *
 */
void dechiffrer()
{
    FILE * fichier;
    FILE * fichier_chif;
    FILE* d_bin = NULL;
    FILE* d_len = NULL;
    FILE* d_sign = NULL;
    FILE* n_bin = NULL;
    FILE* n_len = NULL;
    FILE* n_sign = NULL;
    FILE* mes_bin = NULL;
    FILE* mes_len = NULL;
    FILE* mes_sign = NULL;
    numb d;
    int d_int;
    numb n;
    int n_int;
    char * chemin;
    int message;
    numb message_numb;
    numb res;
    int i;

    d_bin = fopen("Clef privee/d.bin", "rb");
    d_len = fopen("Clef privee/d.len", "rb");
    d_sign = fopen("Clef privee/d.sign", "rb");

    n_bin = fopen("Clef publique/n.bin", "rb");
    n_len = fopen("Clef publique/n.len", "rb");
    n_sign = fopen("Clef publique/n.sign", "rb");

    d.sign=read_int(d_sign);
    d.len=read_int(d.len);
    d.tab=read_tab(d_bin, d.len);
    fclose(d_bin);
    fclose(d_len);
    fclose(d_bin);

    n.sign=read_int(n_sign);
    n.len=read_int(n.len);
    n.tab=read_tab(n_bin, n.len);
    fclose(n_bin);
    fclose(n_len);
    fclose(n_bin);

    printf("Entrez le chemin et nom du fichier a dechiffrer");
    scanf("%s", chemin);

    fichier = fopen(chemin, "rb");
    fichier = fopen(chemin, "rb");

    n_int=0;
    for (i=0; i<=n.len; i++)
    {
        n_int=n_int+pow(10,i)*n.tab[i];
    }
    message=read_message(fichier, n_int);
    message_numb=split(message);
    fclose(fichier);

    d_int=0;
    for (i=0; i<=n.len; i++)
    {
        d_int=d_int+pow(10,i)*d.tab[i];
    }
    res=modulo(puissance(message_numb, d_int), n);


    mes_bin = fopen("message dechiffre/message.bin", "wb");
    mes_len = fopen("message dechiffre/message.len", "wb");
    mes_sign = fopen("message dechiffre/message.sign", "wb");

    fwrite(message_numb.tab , sizeof(int) , message_numb.len+1 , mes_bin);
    fwrite(message_numb.len , sizeof(int) , 1 , mes_len);
    fwrite(message_numb.sign , sizeof(int) , 1 , mes_sign);
    fclose(mes_bin);
    fclose(mes_len);
    fclose(mes_sign);

}

int main()
{
    int choice = 5;
    while (choice != 0)
    {
        printf ("Voulez vous (tapez le numero correspondant):\n1) G�n�rer des clefs privees et publiques ?\n2) Chiffrer un message ?\n3) Dechiffrer un message ?\n\n Tapez 0 pour terminer.");
        scanf("%d", &choice);
        if (choice == 1)
        {
            generate_key();
        }
        if (choice == 2)
        {
            chiffrer();
        }
        if (choice == 3)
        {
            dechiffrer();
        }
    }
    return 0;
}
