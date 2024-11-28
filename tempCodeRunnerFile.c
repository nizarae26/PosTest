#include <stdio.h>
#include <string.h>

typedef struct
{
    int kode;
    char nama[50];
    float harga;
    int stok;
} Produk;

typedef struct
{
    char kodeMember[10];
    char nama[50];
} Member;

void tampilanWelcome(Produk *produk);
void tampilanRingkasan(char name[]);
void ringkasanBarang(Produk *produk, int *jumlah, int total_barang);
int validasiMember(char *kodeMember, Member *member, int jumlahMember);
void daftarMember(Member *member, int *jumlahMember);
void tampilStruk();
void ringkasanBarangStruk(char name[], Produk *produk, int *jumlah, int total_barang);

int main()
{
    char name[50];
    char kodeMember[10];
    Produk produk[] = {
        {1, "Keyboard Mecanical", 230000, 10},
        {2, "Mouse Logitech", 150000, 5},
        {3, "Monitor", 300000, 2}};

    Member members[100];  // Array untuk menyimpan daftar member
    int jumlahMember = 0; // Jumlah member terdaftar

    int jumlah[50] = {0};
    float total_harga = 0, diskon, pembayaran, kembalian;
    int total_barang = 0;
    int jumlah_barang;
    char kar;

ulangi:

    tampilanWelcome(produk);

ulangi_member:

    printf("Masukkan Kode Member (kosongkan jika bukan member): ");
    // scanf(" %s", kodeMember);
    // fgets(  kodeMember, sizeof(kodeMember), stdin);
    gets(kodeMember);
    kodeMember[strcspn(kodeMember, "\n")] = 0; // Menghapus newline

    if (strlen(kodeMember) == 0)
    {
        printf("Anda belum menjadi member. Apakah ingin mendaftar? (Y/T): ");
        scanf(" %c", &kar);
        getchar(); // Membersihkan buffer

        if (kar == 'y' || kar == 'Y')
        {
            daftarMember(members, &jumlahMember);
            goto ulangi_member;
            strcpy(name, members[jumlahMember - 1].nama); // Ambil nama member yang baru didaftarkan
        }
        else
        {
            printf("Nama Pembeli: ");
            getchar(); // Membersihkan buffer sebelum fgets
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0; // Menghapus newline
        }
    }
    else if (validasiMember(kodeMember, members, jumlahMember))
    {
        for (int i = 0; i < jumlahMember; i++)
        {
            if (strcmp(kodeMember, members[i].kodeMember) == 0)
            {
                strcpy(name, members[i].nama); // Ambil nama dari daftar member
                break;
            }
        }
        printf("Selamat datang kembali, %s!\n", name);
    }
    else
    {
        printf("Kode member tidak ditemukan.\n");
        goto ulangi_member;
    }

    do
    {
        int barang;
    ulangi_pilih:
        printf("Pilih no barang (1-3): ");
        scanf(" %d", &barang);

        if (barang < 1 || barang > 3)
        {
            printf("Barang tidak valid, pilih nomor antara 1 sampai 3.\n");
            goto ulangi_pilih;

            // continue;
        }

    ulang:
        printf("Masukkan Jumlah Barang : ");
        scanf("%d", &jumlah_barang);

        if (jumlah_barang > produk[barang - 1].stok)
        {
            printf("Stok tidak cukup untuk %s. Tersisa: %d\n", produk[barang - 1].nama, produk[barang - 1].stok);
            goto ulang;
            // continue;
        }

        total_harga += produk[barang - 1].harga * jumlah_barang;
        jumlah[barang - 1] += jumlah_barang;
        produk[barang - 1].stok -= jumlah_barang;
        total_barang++;

        printf("Apakah ingin memilih barang lagi? (Y/T): ");
        scanf(" %c", &kar);
    } while (kar == 'y' || kar == 'Y');

    tampilanRingkasan(name);
    ringkasanBarang(produk, jumlah, 3);

    // printf("Total Pembelian : Rp %.2f", total_harga);

    if (validasiMember(kodeMember, members, jumlahMember))
    {
        diskon = 0.1 * total_harga;
        total_harga -= diskon;
        printf("\nSELAMAT ANDA MENDAPATKAN DISKON SEBESAR 10 %%\n");
        printf("--------------------------------------------\n");
        printf("Total harga setelah diskon: Rp %.2f\n", total_harga);
    }
    else
    {
        printf("\nMOHON MAAF ANDA BELUM BISA MENDAPATKAN DISKON\n");
        printf("\nTotal harga tanpa: Rp %.2f\n", total_harga);
    }

    printf("======================================");
    do
    {
        printf("\nMasukkan jumlah uang yang dibayar: Rp ");
        scanf("%f", &pembayaran);

        if (pembayaran < total_harga)
        {
            total_harga -= pembayaran;
            printf("Uang yang dibayar kurang. Sisa yang harus dibayar: Rp %.2f\n", total_harga);
            printf("======================================");
        }
        else
        {
            kembalian = pembayaran - total_harga;
            printf("Kembalian: Rp %.2f\n", kembalian);
            total_harga = 0;
        }
    } while (total_harga > 0);

    printf("Terima kasih, %s telah belanja di toko kami.", name);

    printf("\nApakah ingin melakukan transaksi lagi? (Y/T): ");
    scanf(" %c", &kar);
    getchar();
    if (kar == 'y' || kar == 'Y')
    {
        goto ulangi;
    }
    else
    {
        tampilStruk();
    }

    return 0;
}

void tampilanWelcome(Produk *produk)
{
    printf("\t\t\t==================================================================\n");
    printf("\t\t\t|                Selamat datang di Toko Berkah Jaya              |\n");
    printf("\t\t\t|                    Sedia Berbagai Komponen                     |\n");
    printf("\t\t\t|                          Elektronika                           |\n");
    printf("\t\t\t+====+===============================+==================+========+\n");
    printf("\t\t\t| No |        Nama Barang            |\tHarga\t\t|  Stok  |\n");
    printf("\t\t\t+====+===============================+==================+========+\n");
    for (int i = 0; i < 3; i++)
    {
        printf("\t\t\t| %d  | %-30s|\tRp %.2f\t| %-6d |\n", i + 1, produk[i].nama, produk[i].harga, produk[i].stok);
    }
    printf("\t\t\t+====+===============================+==================+========+\n");
}

void tampilanRingkasan(char name[])
{
    printf("+====+===============================+========+=================+===============+\n");
    printf("                     RINGKASAN PEMBELIAN UNTUK %s\n", name);
    printf("+====+===============================+========+=================+===============+\n");
    printf("| No |        Nama Barang            | Jumlah |\tHarga\t\t|  Total Harga  |\n");
    printf("+====+===============================+========+=================+===============+\n");
}

void ringkasanBarang(Produk *produk, int *jumlah, int total_barang)
{
    for (int i = 0; i < total_barang; i++)
    {
        if (jumlah[i] > 0)
        {
            printf("| %-2d | %-30s| %-6d |\tRp %.2f\t| Rp %.2f\t|\n",
                   i + 1, produk[i].nama, jumlah[i], produk[i].harga, jumlah[i] * produk[i].harga);
        }
    }
    printf("+====+===============================+========+=================+===============+\n");
}

int validasiMember(char *kodeMember, Member *member, int jumlahMember)
{
    for (int i = 0; i < jumlahMember; i++)
    {
        if (strcmp(kodeMember, member[i].kodeMember) == 0)
        {
            return 1; // Member valid
        }
    }
    return 0; // Member tidak ditemukan
}

void daftarMember(Member *member, int *jumlahMember)
{
    char kode[10], nama[50];

    printf("\nMasukkan Kode Member Baru: ");
    scanf("%s", kode);
    getchar(); // Mengatasi masalah buffer
    printf("Masukkan Nama Member Baru: ");
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = 0;

    strcpy(member[*jumlahMember].kodeMember, kode);
    strcpy(member[*jumlahMember].nama, nama);
    (*jumlahMember)++;

    printf("Pendaftaran berhasil! Selamat menjadi member.\n");
}

void ringkasanBarangStruk(char name[], Produk *produk, int *jumlah, int total_barang)
{
    printf("\t\t\t|| Nama Pelanggan: %-45s ||\n", name);
    printf("\t\t\t==================================================================\n");
    for (int i = 0; i < total_barang; i++)
    {
        if (jumlah[i] > 0)
        {
            printf("| %-2d | %-30s| %-6d |\tRp %.2f\t| Rp %.2f\t|\n",
                   i + 1, produk[i].nama, jumlah[i], produk[i].harga, jumlah[i] * produk[i].harga);
        }
    }
    printf("+====+===============================+========+=================+===============+\n");
}

void tampilStruk()
{

    printf("\t\t\t==================================================================\n");
    printf("\t\t\t||                       Toko Berkah Jaya                       ||\n");
    printf("\t\t\t||        Jalan Raya ITS - Kampus PENS, Sukolilo, Surabaya      ||\n");
    printf("\t\t\t||                        080-1234-5678                         ||\n");
    printf("\t\t\t==================================================================\n");
    ringkasanBarangStruk(name, produk, jumlah, total_barang);
    printf("\t\t\t|| Nama Barang                 Jumlah           Harga           || \n");
    printf("\t\t\t==================================================================\n");
}
