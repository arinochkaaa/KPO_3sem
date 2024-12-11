.586P                                                  ; ������� ��������� (��������� Pentium)
.MODEL FLAT, STDCALL                                   ; ������ ������, ���������� � ������
includelib kernel32.lib                                ; ������������: ����������� � kernel32

ExitProcess PROTO :DWORD                              ; �������� ������� ��� ���������� �������� Windows
MessageBoxA PROTO :DWORD, :DWORD, :DWORD, :DWORD      ; �������� API-������� MessageBoxA

.STACK 4096                                            ; ��������� �����

.CONST                                                 ; ������� ��������

.DATA                                                  ; ������� ������
MB_OK EQU 0                                            ; EQU ���������� ���������
STR1 DB "��� ������ ���������", 0                    ; ������, ������ ������� ������ + ������� ���
STR2 DB "����� �����!", 0                            ; ������, ������ ������� ������ + ������� ���
STR3 DB "������ ����!", 0              ; ������ ��� ������� ���������
HW DD ?                                                ; ������� ����� ������ 4 �����, ������������������

.CODE                                                  ; ������� ����

main PROC                                              ; ����� ����� main
START:                                                 ; �����
        PUSH MB_OK
        PUSH OFFSET STR1
        PUSH OFFSET STR2
        PUSH HW
        CALL MessageBoxA                               ; ����� ������ ������� MessageBoxA

        ; ������ ���� ���������
        PUSH MB_OK
        PUSH OFFSET STR1
        PUSH OFFSET STR3
        PUSH HW
        CALL MessageBoxA                               ; ����� ������ ������� MessageBoxA

        PUSH -1                                        ; ��� �������� �������� Windows (�������� ExitProcess)
        CALL ExitProcess                               ; ����� ���������
main ENDP

end main                                               ; ����� ������ main
