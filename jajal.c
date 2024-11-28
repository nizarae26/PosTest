#include <stdio.h>
#include <string.h>

// Struktur Produk
typedef struct {
    int kode;
    char nama[50];
    float harga;
    int stok;
} Produk;

// Struktur Member
typedef struct {
    char kodeMember[10];
    char nama[50];
} Member;

// Fungsi Prototipe
void tampilWelcome(Produk *produk);
void tampilRingkasan(char name[]);
void tampilStruk(char name[], Produk *produk, int *jumlah, int total_barang, int total_qty, float grand_total, float pembayaran, float kembalian);
void daftarMember(Member *member, int *jumlahMember);
void tampilRingkasanBarang(Produk *produk, int *jumlah, int total_barang);
int validasiMember(char *kodeMember, Member *member, int jumlahMember);

// Program Utama
int main() {
    char name[50];
    char kodeMember[10];
    Produk produk[] = {
        {1, "Keyboard Mechanical", 230000, 10},
        {2, "Mouse Logitech", 150000, 5},
        {3, "Monitor", 300000, 2}
    };

    Member members[100];
    int jumlahMember = 0;

    int jumlah[50] = {0};
    float grand_total = 0, diskon = 0, pembayaran, kembalian;
    int total_barang = 3, total_qty = 0, jumlah_barang;
    char ulang;

ulangi_transaksi:
    tampilWelcome(produk);

    // Memasukkan Kode Member
    printf("Masukkan Kode Member (kosongkan jika bukan member): ");
    fgets(kodeMember, sizeof(kodeMember), stdin);
    kodeMember[strcspn(kodeMember, "\n")] = 0;

    if (strlen(kodeMember) == 0) {
        printf("Nama Pembeli: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
    } else if (validasiMember(kodeMember, members, jumlahMember)) {
        for (int i = 0; i < jumlahMember; i++) {
            if (strcmp(kodeMember, members[i].kodeMember) == 0) {
                strcpy(name, members[i].nama);
                break;
            }
        }
        printf("Selamat datang kembali, %s!\n", name);
    } else {
        printf("Kode member tidak ditemukan.\n");
        goto ulangi_transaksi;
    }

    // Pemilihan Barang
    do {
        int pilihan_barang;
        printf("\nPilih nomor barang (1-3): ");
        scanf("%d", &pilihan_barang);

        if (pilihan_barang < 1 || pilihan_barang > total_barang) {
            printf("Nomor barang tidak valid. Silakan ulangi.\n");
            continue;
        }

        printf("Masukkan jumlah barang: ");
        scanf("%d", &jumlah_barang);

        if (jumlah_barang > produk[pilihan_barang - 1].stok) {
            printf("Stok tidak mencukupi. Sisa stok: %d\n", produk[pilihan_barang - 1].stok);
            continue;
        }

        jumlah[pilihan_barang - 1] += jumlah_barang;
        produk[pilihan_barang - 1].stok -= jumlah_barang;
        total_qty += jumlah_barang;
        grand_total += jumlah_barang * produk[pilihan_barang - 1].harga;

        printf("Apakah ingin membeli barang lain? (Y/T): ");
        scanf(" %c", &ulang);
    } while (ulang == 'Y' || ulang == 'y');

    // Menampilkan Ringkasan Barang
    tampilRingkasan(name);
    tampilRingkasanBarang(produk, jumlah, total_barang);

    // Diskon Member
    if (validasiMember(kodeMember, members, jumlahMember)) {
        diskon = 0.1 * grand_total;
        printf("\nDiskon 10%% sebagai member: Rp %.2f\n", diskon);
        grand_total -= diskon;
    }

    // Pembayaran
    printf("\nTotal yang harus dibayar: Rp %.2f\n", grand_total);
    do {
        printf("Masukkan jumlah pembayaran: Rp ");
        scanf("%f", &pembayaran);

        if (pembayaran < grand_total) {
            printf("Pembayaran kurang. Silakan tambah Rp %.2f.\n", grand_total - pembayaran);
        } else {
            kembalian = pembayaran - grand_total;
            break;
        }
    } while (1);

    // Menampilkan Struk
    tampilStruk(name, produk, jumlah, total_barang, total_qty, grand_total, pembayaran, kembalian);

    // Transaksi Ulang
    printf("\nApakah ingin melakukan transaksi lain? (Y/T): ");
    scanf(" %c", &ulang);
    getchar();

    if (ulang == 'Y' || ulang == 'y') {
        goto ulangi_transaksi;
    }

    return 0;
}

// Implementasi Fungsi Tambahan
void tampilWelcome(Produk *produk) {
    printf("\n+====+=========================+=============+========+\n");
    printf("| No | Nama Barang             | Harga       | Stok   |\n");
    printf("+====+=========================+=============+========+\n");
    for (int i = 0; i < 3; i++) {
        printf("| %-2d | %-23s | Rp %-9.2f | %-6d |\n", i + 1, produk[i].nama, produk[i].harga, produk[i].stok);
    }
    printf("+====+=========================+=============+========+\n");
}

void tampilRingkasan(char name[]) {
    printf("\n+====+=========================+========+=============+\n");
    printf("| No | Nama Barang             | Jumlah | Total       |\n");
    printf("+====+=========================+========+=============+\n");
}

void tampilRingkasanBarang(Produk *produk, int *jumlah, int total_barang) {
    for (int i = 0; i < total_barang; i++) {
        if (jumlah[i] > 0) {
            printf("| %-2d | %-23s | %-6d | Rp %-9.2f |\n",
                   i + 1, produk[i].nama, jumlah[i], jumlah[i] * produk[i].harga);
        }
    }
    printf("+====+=========================+========+=============+\n");
}

void tampilStruk(char name[], Produk *produk, int *jumlah, int total_barang, int total_qty, float grand_total, float pembayaran, float kembalian) {
    printf("\n============= STRUK PEMBELIAN =============\n");
    printf("Nama Pembeli: %s\n", name);
    printf("===========================================\n");
    for (int i = 0; i < total_barang; i++) {
        if (jumlah[i] > 0) {
            printf("%-23s %-4d x Rp %-9.2f = Rp %-9.2f\n",
                   produk[i].nama, jumlah[i], produk[i].harga, jumlah[i] * produk[i].harga);
        }
    }
    printf("===========================================\n");
    printf("Total Qty   : %d\n", total_qty);
    printf("Grand Total : Rp %.2f\n", grand_total);
    printf("Bayar (Cash): Rp %.2f\n", pembayaran);
    printf("Kembalian   : Rp %.2f\n", kembalian);
    printf("===========================================\n");
}

int validasiMember(char *kodeMember, Member *member, int jumlahMember) {
    for (int i = 0; i < jumlahMember; i++) {
        if (strcmp(kodeMember, member[i].kodeMember) == 0) {
            return 1;
        }
    }
    return 0;
}
