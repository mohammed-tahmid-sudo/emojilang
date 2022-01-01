from lark.tree import Tree
from lark.visitors import Visitor_Recursive


class EmojiLangTransformer(Visitor_Recursive):
    def if_stmt(self, tree: Tree):
        for i in range(0, len(tree.children)):
            if tree.children[i] == '🚩':
                tree.children[i] = 'if'
            elif tree.children[i] == '🏳':
                tree.children[i] = 'elif'
            elif tree.children[i] == '🏁':
                tree.children[i] = 'else'
        # return tree.children

        # print(tree.children)

    def boolean(self, tree: Tree):
        if tree.children[0] == '✔':
            tree.children[0] = "true"
        else:
            tree.children[0] = "false"
        # return tree.children

    def castexpression(self, tree: Tree):
        if len(tree.children) == 1:
            return
            # return tree.children
        else:  # the tree size is 2 and first child is the unarary operator
            if tree.children[0] == '❗':
                tree.children[0] = '!'
            else:
                tree.children[0] = '~'
        # return tree.children

    def multiplicativeexpression(self, tree: Tree):
        for i in range(1, len(tree.children)):
            if tree.children[i] == '✖':
                tree.children[i] = '*'
            elif tree.children[i] == '➗':
                tree.children[i] = '/'
            elif tree.children[i] == '📎':
                tree.children[i] = '%'
        # return tree.children

    def additiveexpression(self, tree: Tree):
        for i in range(1, len(tree.children)):
            if tree.children[i] == '➕':
                tree.children[i] = '+'
            elif tree.children[i] == '➖':
                tree.children[i] = '-'
        # return tree.children

    def getMatch(self, child):
        mappings = {
            "😭":   "<",
            "😁":   ">",
            "😁😌": ">=",
            "😭😌":  "<=",
            "😌😌":  "==",
            "❗😌":  "!="
        }
        return mappings[child]

    def equalityexpression(self, tree: Tree):
        for i in range(1, len(tree.children)):
            if tree.children[i] in ["😭",
                                    "😁",
                                    "😁😌",
                                    "😭😌",
                                    "😌😌",
                                    "❗😌"]:
                tree.children[i] = self.getMatch(tree.children[i])
        # return tree.children

    def andexpression(self, tree: Tree):
        for i in range(1, len(tree.children)):
            if tree.children[i] == '⚛':
                tree.children[i] = '&'
        # return tree.children

    def exclusiveorexpression(self, tree: Tree):
        for i in range(1, len(tree.children)):
            if tree.children[i] == '⚓':
                tree.children[i] = 'xor'
        # return tree.children

    def inclusiveorexpression(self, tree: Tree):
        for i in range(1, len(tree.children)):
            if tree.children[i] == '☯':
                tree.children[i] = '|'
        # return tree.children

    def logicalandexpression(self, tree: Tree):
        for i in range(1, len(tree.children)):
            if tree.children[i] == '😠':
                tree.children[i] = 'and'
        # return tree.children

    def logicalorexpression(self, tree: Tree):
        for i in range(1, len(tree.children)):
            if tree.children[i] == '😇':
                tree.children[i] = 'or'
        # return tree.children
