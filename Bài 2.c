#include <stdio.h>
#include <string.h>
#define MAX_VE 50

struct VeSuKien {
    int maVe;
    char tenSuKien[50];
    char loaiVe[20];
    float giaGoc;
    int isEarlyBird;
    int daCheckIn;
};

float tinhGiaVe(float giaGoc, int isEarlyBird);

int timVeTheoMa(const struct VeSuKien dsVe[], int soLuongVe, int maVe);

int phatHanhVe(struct VeSuKien dsVe[], int soLuongVe, struct VeSuKien veMoi);

int checkInQR(struct VeSuKien dsVe[], int soLuongVe, int maVe);
             
int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe);

void hienThiDanhSachVe(const struct VeSuKien dsVe[], int soLuongVe);
                      
int main() {
    struct VeSuKien dsVe[MAX_VE] = {
        {1001, "Live Concert VIBE 2025", "VIP", 2000000, 1, 0},
        {1002, "Live Concert VIBE 2025", "GA", 800000, 0, 0},
        {1003, "Live Concert VIBE 2025", "Zone A", 1200000, 1, 0}
    };

    int soLuongVe = 3;
    int ketQua;

    printf("=== QUAN LY VE TICKETBOX ===\n");

    printf("\n1. DANH SACH VE BAN DAU\n");
    hienThiDanhSachVe(dsVe, soLuongVe);

    printf("\n2. PHAT HANH VE MOI\n");

    struct VeSuKien veMoi = {
        1004, "Live Concert VIBE 2025", "VIP", 2500000, 0, 0
    };

    soLuongVe = phatHanhVe(dsVe, soLuongVe, veMoi);

    printf("\n3. CHECK-IN VE 1001\n");
    ketQua = checkInQR(dsVe, soLuongVe, 1001);

    printf("\n4. QUET LAI VE 1001\n");
    ketQua = checkInQR(dsVe, soLuongVe, 1001);

    printf("\n5. HUY VE 1002\n");
    soLuongVe = huyVe(dsVe, soLuongVe, 1002);

    printf("\n6. CHECK-IN VE 9999\n");
    ketQua = checkInQR(dsVe, soLuongVe, 9999);

    printf("\n7. DANH SACH VE SAU THAO TAC\n");
    hienThiDanhSachVe(dsVe, soLuongVe);

    return 0;
}

float tinhGiaVe(float giaGoc, int isEarlyBird) {
    if (isEarlyBird == 1) {
        return giaGoc * 0.85f;
    }

    return giaGoc;
}

int timVeTheoMa(const struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    int i;

    for (i = 0; i < soLuongVe; i++) {
        if (dsVe[i].maVe == maVe) {
            return i;
        }
    }

    return -1;
}

int phatHanhVe(struct VeSuKien dsVe[], int soLuongVe, struct VeSuKien veMoi) {
    if (soLuongVe >= MAX_VE) {
        printf("[LOI] Danh sach ve da day!\n");
        return soLuongVe;
    }

    if (timVeTheoMa(dsVe, soLuongVe, veMoi.maVe) != -1) {
        printf("[LOI] Ma ve %d da ton tai!\n", veMoi.maVe);
        return soLuongVe;
    }

    dsVe[soLuongVe] = veMoi;
    soLuongVe++;

    printf("[THANH CONG] Da phat hanh ve %d.\n", veMoi.maVe);

    return soLuongVe;
}

int checkInQR(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    int viTri;

    if (soLuongVe == 0) {
        printf("[LOI] Danh sach ve dang rong!\n");
        return 0;
    }

    viTri = timVeTheoMa(dsVe, soLuongVe, maVe);

    if (viTri == -1) {
        printf("[LOI] Ma ve %d khong ton tai!\n", maVe);
        return 0;
    }

    if (dsVe[viTri].daCheckIn == 1) {
        printf("[CANH BAO] Ve %d da check-in! Tu choi quet lai.\n",
               maVe);
        return 0;
    }

    dsVe[viTri].daCheckIn = 1;

    printf("[THANH CONG] Ve %d check-in thanh cong.\n", maVe);

    return 1;
}

int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    int viTri;
    int i;

    if (soLuongVe == 0) {
        printf("[LOI] Khong co ve de huy!\n");
        return soLuongVe;
    }

    viTri = timVeTheoMa(dsVe, soLuongVe, maVe);

    if (viTri == -1) {
        printf("[LOI] Khong tim thay ve %d de huy!\n", maVe);
        return soLuongVe;
    }

    for (i = viTri; i < soLuongVe - 1; i++) {
        dsVe[i] = dsVe[i + 1];
    }

    soLuongVe--;

    printf("[THANH CONG] Da huy ve %d.\n", maVe);

    return soLuongVe;
}

void hienThiDanhSachVe(const struct VeSuKien dsVe[], int soLuongVe) {
    int i;

    if (soLuongVe == 0) {
        printf("Danh sach ve dang rong!\n");
        return;
    }

    for (i = 0; i < soLuongVe; i++) {
        printf("Ma ve: %d | Su kien: %s | Loai: %s\n",
               dsVe[i].maVe,
               dsVe[i].tenSuKien,
               dsVe[i].loaiVe);

        printf("Gia goc: %.0f VND | Gia thanh toan: %.0f VND\n",
               dsVe[i].giaGoc,
               tinhGiaVe(dsVe[i].giaGoc, dsVe[i].isEarlyBird));

        if (dsVe[i].daCheckIn == 1) {
            printf("Trang thai: Da check-in\n");
        } else {
            printf("Trang thai: Chua check-in\n");
        }

        printf("----------------------------------------\n");
    }

    printf("Tong so ve: %d\n", soLuongVe);
}

