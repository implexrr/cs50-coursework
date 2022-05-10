from cs50 import get_string


def main():
    # Prompt user for text
    text = get_string("Text: ")

    # Count number of letters, words and strings in text
    letter_count = count_letters(text)
    word_count = count_words(text)
    sentence_count = count_sentences(text)
    if letter_count > 1:
        word_count += 1

    # Calculate Coleman-Liau Index, return reading level to terminal
    coleman_liau(letter_count, word_count, sentence_count)


def count_letters(text):
    """ Calculate number of letters in a string """
    n = len(text)
    letter_count = 0
    for i in range(n):
        if ((ord(text[i]) >= ord('A') and ord(text[i]) <= ord('Z'))
                or (ord(text[i]) >= ord('a') and ord(text[i]) <= ord('z'))):
            letter_count += 1
    return letter_count


def count_words(text):
    """ Calculate number of words in a string """
    n = len(text)
    word_count = 0
    for i in range(n):
        if text[i] == ' ':
            word_count += 1
    return word_count


def count_sentences(text):
    """ Calculate number of sentences in a string """
    sentence_count = 0
    n = len(text)
    for i in range(n):
        if text[i] == '!' or text[i] == '.' or text[i] == '?':
            sentence_count += 1
    return sentence_count


def coleman_liau(letter_count, word_count, sentence_count):
    """ Calculate CL index, round to nearest integer
    and map integer to corresponding reading level"""
    index = (0.0588 * 100 * letter_count / word_count) - (0.296 * 100 * sentence_count / word_count) - 15.8
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        int(round(index))
        print("Grade " + str(round(index)))


if __name__ == "__main__":
    main()