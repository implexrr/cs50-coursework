import cs50
AMEX_LENGTH = 15
MASTERCARD_LENGTH = 16
VISA_LENGTH = 13  # Or 16, but MASTERCARD_LENGTH will check for that already


def main():
    cc_number = cs50.get_string("Number: ")

    # Check if credit card satisfies Luhn's Algorithm
    if luhn_valid(cc_number) == True:
        print(card_type(cc_number))
    else:
        print("INVALID")


# Luhn's Algorithm
def luhn_valid(cc_number):
    sum = 0
    for i in range(len(cc_number) - 2, -1, -2):
        temp = int(cc_number[i]) * 2
        if temp >= 10:
            sum += (temp % 10 + temp // 10)
        else:
            sum += temp
    for i in range(len(cc_number) - 1, -1, -2):
        temp = int(cc_number[i])
        sum += temp
    if sum % 10 == 0:
        return True
    else:
        return False


def card_type(cc_number):
    # Check credit card type
    if len(cc_number) == AMEX_LENGTH and (cc_number[0:2] == "34" or cc_number[0:2] == "37"):
        card_type = "AMEX"
    elif len(cc_number) == MASTERCARD_LENGTH and int(cc_number[0:2]) >= 51 and int(cc_number[0:2]) <= 55:
        card_type = "MASTERCARD"
    elif (len(cc_number) == MASTERCARD_LENGTH or len(cc_number) == VISA_LENGTH) and cc_number[0] == "4":
        card_type = "VISA"
    else:
        card_type = "INVALID"
    return card_type


if __name__ == "__main__":
    main()

