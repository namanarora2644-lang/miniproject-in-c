#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MENU_SIZE 10
#define MAX_ORDER 20
#define NAME_LEN 30
#define GST 5.0
#define DISCOUNT 10.0

char menu[MENU_SIZE][NAME_LEN] = {
    "Paneer Butter Masala", "Dal Makhani", "Butter Naan",
    "Veg Biryani", "Chicken Biryani", "Masala Dosa",
    "Veg Burger", "French Fries", "Cold Coffee", "Gulab Jamun"
};

float price[MENU_SIZE] = {
    240, 180, 40, 160, 220, 90, 80, 70, 100, 60
};

int item[MAX_ORDER], qty[MAX_ORDER];
int count = 0, billNo = 1;

int readInt()
{
    int n, c;

    if (scanf("%d", &n) != 1)
    {
        while ((c = getchar()) != '\n' && c != EOF);
        return -1;
    }

    while ((c = getchar()) != '\n' && c != EOF);
    return n;
}

void showMenu()
{
    printf("\n----------- MENU -----------\n");

    for (int i = 0; i < MENU_SIZE; i++)
        printf("%d. %-24s Rs %.2f\n", i + 1, menu[i], price[i]);

    printf("----------------------------\n");
}

int findItem(int x)
{
    for (int i = 0; i < count; i++)
    {
        if (item[i] == x)
            return i;
    }
    return -1;
}

void addItem()
{
    int choice, q;

    showMenu();

    printf("Enter item number: ");
    choice = readInt();

    if (choice < 1 || choice > MENU_SIZE)
    {
        printf("Invalid item!\n");
        return;
    }

    printf("Enter quantity: ");
    q = readInt();

    if (q <= 0)
    {
        printf("Invalid quantity!\n");
        return;
    }

    int pos = findItem(choice - 1);

    if (pos != -1)
        qty[pos] += q;
    else
    {
        if (count >= MAX_ORDER)
        {
            printf("Order is full!\n");
            return;
        }

        item[count] = choice - 1;
        qty[count] = q;
        count++;
    }

    printf("Item added successfully.\n");
}

void viewOrder()
{
    if (count == 0)
    {
        printf("No items in order.\n");
        return;
    }

    printf("\n--------- ORDER ---------\n");

    for (int i = 0; i < count; i++)
    {
        int x = item[i];
        printf("%d. %s x %d = Rs %.2f\n",
               i + 1, menu[x], qty[i], price[x] * qty[i]);
    }
}

void removeItem()
{
    int ch, pos;

    viewOrder();

    if (count == 0)
        return;

    printf("Enter item number to remove: ");
    ch = readInt();

    if (ch < 1 || ch > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    pos = ch - 1;

    for (int i = pos; i < count - 1; i++)
    {
        item[i] = item[i + 1];
        qty[i] = qty[i + 1];
    }

    count--;
    printf("Item removed.\n");
}

void bill()
{
    char name[NAME_LEN];
    int table;
    float subtotal = 0, discount = 0, gst, total;

    if (count == 0)
    {
        printf("No items ordered.\n");
        return;
    }

    printf("Enter customer name: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter table number: ");
    table = readInt();

    for (int i = 0; i < count; i++)
        subtotal += price[item[i]] * qty[i];

    if (subtotal > 1000)
        discount = subtotal * DISCOUNT / 100;

    gst = (subtotal - discount) * GST / 100;
    total = subtotal - discount + gst;

    printf("\n==============================\n");
    printf("     SPICE GARDEN RESTAURANT\n");
    printf("==============================\n");
    printf("Bill No: %d\n", billNo);
    printf("Customer: %s\n", name);
    printf("Table: %d\n", table);

    viewOrder();

    printf("------------------------------\n");
    printf("Subtotal : Rs %.2f\n", subtotal);
    printf("Discount : Rs %.2f\n", discount);
    printf("GST      : Rs %.2f\n", gst);
    printf("Total    : Rs %.2f\n", total);
    printf("==============================\n");
    printf("Thank you! Visit again.\n");

    billNo++;
    count = 0;
}

int main()
{
    int ch;

    do
    {
        printf("\n===== RESTAURANT BILLING SYSTEM =====\n");
        printf("1. Show Menu\n");
        printf("2. Add Item\n");
        printf("3. Remove Item\n");
        printf("4. View Order\n");
        printf("5. Generate Bill\n");
        printf("6. Clear Order\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        ch = readInt();

        switch (ch)
        {
            case 1:
                showMenu();
                break;

            case 2:
                addItem();
                break;

            case 3:
                removeItem();
                break;

            case 4:
                viewOrder();
                break;

            case 5:
                bill();
                break;

            case 6:
                count = 0;
                printf("Order cleared.\n");
                break;

            case 7:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (ch != 7);

    return 0;
}