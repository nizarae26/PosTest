#include <stdio.h>


int main()
{
    char name[50] = "Keyboard Mecanical";
    char nama[50] = "Welut";
    int jumlah = 2;
    int harga = 200000;
    float totalsementara = jumlah * harga;

    printf("\t\t\t==================================================================\n");
    printf("\t\t\t||                       Toko Berkah Jaya                       ||\n");
    printf("\t\t\t||        Jalan Raya ITS - Kampus PENS, Sukolilo, Surabaya      ||\n");
    printf("\t\t\t||                        080-1234-5678                         ||\n");
    printf("\t\t\t||--------------------------------------------------------------||\n");
    printf("\t\t\t|| \t\t\t\t\t Nama Pelanggan : %s ||\n", nama);
    printf("\t\t\t||--------------------------------------------------------------||\n");
    printf("\t\t\t|| %-60s ||\n", name);
    printf("\t\t\t|| %-2dX %-45d  %-.2f ||\n", jumlah, harga, totalsementara);
    printf("\t\t\t||--------------------------------------------------------------||\n");
    printf("\t\t\t|| Total Qty : %-47d  ||\n", jumlah);
    printf("\t\t\t||\t\t\t\t\t\t\t\t||\n", jumlah);
    printf("\t\t\t|| Grand Total\t\t\t\t\t   Rp %-.2f ||\n", totalsementara);
    printf("\t\t\t|| Bayar (Cash)\t\t\t\t\t   Rp %-.2f ||\n", totalsementara);
    printf("\t\t\t||--------------------------------------------------------------||\n");
    printf("\t\t\t|| Kembalian\t\t\t\t\t   Rp %-.2f ||\n", totalsementara);
    printf("\t\t\t||\t\t\t\t\t\t\t\t||\n");
    printf("\t\t\t|| \t\t  TERIMAKASIH ATAS KUNJUNGAN ANDA\t\t||\n");
    printf("\t\t\t||\tBARANG YANG SUDAH DIBELI TIDAK BISA DIKEMBALIKAN\t||\n");
    printf("\t\t\t||\t\t\t\t\t\t\t\t||\n");
    printf("\t\t\t==================================================================\n");

    return 0;
}
