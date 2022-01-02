import sys, os, pathlib
import lark
# import sys

from EmojiInterpreter import EmojiLangInterpeter
from EmojiTransformer import EmojiLangTransformer


if __name__ == "__main__":
    file, parser = None, None
    try:
        file = open(os.path.join("emojiGrammar.lark"), "r", errors="ignore", encoding="utf8")
    except:
        print("STATUS:error in opening the file")
        sys.exit()

    parser = lark.Lark(file, start="stmt")
    print("STATUS:Parser Generated Succesfully")
    print('-----------------------------------------------------------------------------')
    testFileNames = os.listdir(os.path.join("tests"))
    isTest = True
    if len(sys.argv) > 1:
        testFileNames = sys.argv[1:]
        isTest = False
        # print(sys.argv)
    
    for filName in testFileNames:
        text = None
        try:
            if filName.endswith(".emo"):
                if isTest:
                    text = pathlib.Path(os.path.join("tests", filName)).read_text(errors="ignore", encoding="utf8")
                else:
                    text = pathlib.Path(os.path.join(filName)).read_text(errors="ignore", encoding="utf8")
            else:
                print("Please give a valid file to execute ...that ends with .emo")
                sys.exit()
        except:
            if isTest:
                print(f"STATUS:error in reading the file tests/{filName}")
            else:
                print(f"STATUS:error in reading the file /{filName}")
            sys.exit()
        text += '\n'
        tree = None
        tree = parser.parse(text)
        print(f"STATUS:{filName} Parsed Successfully")
        # print(tree.pretty())
        EmojiLangTransformer().visit(tree)
        # print(tree.pretty())
        runner = EmojiLangInterpeter(tree)
        runner.start()
        print(f"STATUS:{filName} ran without any interrupt")
        print('-----------------------------------------------------------------------------')