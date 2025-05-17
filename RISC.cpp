
unsigned 
    MOV = 0, LSL = 1, ASR = 2, ROR = 3, AND = 4, ANN = 5, IOR = 6, XOR = 7,
    ADD = 8, SUB = 9, MUL = 10, DIV = 11;

int IR;   /*instruction register*/
int PC;   /*program counter*/
bool N, Z;  /*condition flags*/
int R[16];
int H;  /*aux register for division*/

#define LEN(arr) (*(&arr + 1) - arr)
#define ODD(x) ((x % 2) == 1)
#define ASH(x, y) (x >> y)

void Execute(int *M, int pc)
//      VAR S: Texts.Scanner; VAR W: Texts.Writer);
{
    int a, b, op, im;  /*instruction fields*/
    int adr, A, B, C;
    int MemSize;

    PC = 0;
    R[13] = pc * 4;
    R[14] = LEN(M) * 4;
    do /*interpretation cycle*/
    {
        IR = M[PC];
        PC++;
        a = IR / 0x1000000 % 0x10;
        b = IR / 0x100000 % 0x10;
        op = IR / 0x10000 % 0x10;
        im = IR / 0x10000;
        if (!ODD(ASH(IR, -31)))
        {  /*~p:  register instruction*/
            /*
            B = R[b];
            IF ~ODD(ASH(IR, -30)) THEN (*~q*)
                C := R[IR MOD 10H]
            ELSIF ~ODD(ASH(IR, -28)) THEN (*q&~v*)
                C := im 
            ELSE (*q&v*)
                C := im + 0FFFF0000H
            END ;
            CASE op OF
                MOV: IF ~ODD(ASH(IR, -29)) THEN A := C ELSE A := H END |
                LSL: A := SYSTEM.LSH(B, C) |
                ASR: A := ASH(B, -C) |
                ROR: A := SYSTEM.ROT(B, -C) |
                AND: A := SYSTEM.VAL(LONGINT, SYSTEM.VAL(SET, B) * SYSTEM.VAL(SET, C)) |
                ANN: A := SYSTEM.VAL(LONGINT, SYSTEM.VAL(SET, B) - SYSTEM.VAL(SET, C)) |
                IOR: A := SYSTEM.VAL(LONGINT, SYSTEM.VAL(SET, B) + SYSTEM.VAL(SET, C)) |
                XOR: A := SYSTEM.VAL(LONGINT, SYSTEM.VAL(SET, B) / SYSTEM.VAL(SET, C)) |
                ADD: A := B + C |
                SUB: A := B - C |
                MUL: A := B * C |
                Div: A := B DIV C; H := B MOD C
            END ;
            R[a] := A; N := A < 0; Z := A = 0
            */
         }
         else if (~ODD(ASH(IR, -30)))
         { /*p & ~q: memory instruction*/
            /*
            adr := (R[b] + IR MOD 100000H) DIV 4;
            IF ~ODD(ASH(IR, -29)) THEN
            IF adr >= 0 THEN (*load*)
                R[a] := M[adr];
                N := A < 0;
                Z := A = 0
            ELSE (*input*)
                IF adr = -1 THEN (*ReadInt*)
                    Texts.Scan(S); R[a] := S.i;
                ELSIF adr = -2 THEN (*eot*)
                    Z := S.class # Texts.Int
                END 
            END
            ELSE
            IF adr >= 0 THEN (*store*) M[adr] := R[a];
            ELSE (*output*);
                IF adr = -1 THEN Texts.WriteInt(W, R[a], 4)
                ELSIF adr = -2 THEN Texts.Write(W, CHR(R[a] MOD 80H))
                ELSIF adr = -3 THEN Texts.WriteLn(W); Texts.Append(Oberon.Log, W.buf)
                END
            END
            END
            */
        }
        else
        { /* p & q: branch instruction*/
            /*
            IF (a = 0) & N OR (a = 1) & Z OR (a = 5) & N OR (a = 6) & (N OR Z) OR (a = 7) OR
                (a = 8) & ~N OR (a = 9) & ~Z OR (a = 13) & ~N OR (a = 14) & ~(N OR Z) THEN
            IF ODD(ASH(IR, -28)) THEN R[15] := PC * 4 END ;
            IF ODD(ASH(IR, -29)) THEN PC := (PC + (IR MOD 1000000H)) MOD 40000H 
            ELSE PC := R[IR MOD 10H] DIV 4
            END
            END
            */
        }
    } while (PC != 0);
    //Texts.Append(Oberon.Log, W.buf)
}

int main(int argc, char **argv)
{
    return 0;
}
