# Analysis
Grammar

Program → Begin Descriptions Operators End
Begin → PROGRAM Id
End → END Id
Descriptions → Descr | Descr Descriptions
Operators→ Op | Op Operators
Descr → Type VarList
Type → INTEGER | COMPLEX
VarList → Id | Id , VarList
Op → Id = Expr
SimpleExpr → Id | Const | ( Expr ) | CMPLX ( Expr , Expr ) | CABS ( Expr )
Expr → SimpleExpr | SimpleExpr + Expr | SimpleExpr - Expr
Id → Letter | Letter Id
Const → IntNum | ComplexNum
IntNum → Digit | Digit IntNum
ComplexNum → ( IntNum , IntNum )
Digit → 0 | 1 | . . . | 9
Letter → a | b | . . . | z | A | B | . . . | Z
