unit MainUnit;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, RegExpr, Math;

type
  TMainForm = class(TForm)
    btnOpenFile: TButton;
    btnStart: TButton;
    memSource: TMemo;
    memResult: TMemo;
    dlOpenFile: TOpenDialog;
    procedure btnStartClick(Sender: TObject);
    procedure btnOpenFileClick(Sender: TObject);
    procedure memSourceChange(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;
  source: string;
  const_strings: array of string;
  const_string_pos: array of array [1..2] of integer;
  program_complexity, predicat_complexity, max_predicat, arc_count, vertex_count, case_count: integer;
  predicat_str: string;
  RegExpr, SubExpr: TRegExpr;

implementation

{$R *.dfm}

function isInRang(position: integer): boolean;
var
  i: integer;
begin
  Result:= false;
  for i := 0 to Length(const_string_pos)-1 do
  begin
    if (position>const_string_pos[i][1]) and (position<const_string_pos[i][2]) then
      Result:= true;
  end;
end;

procedure TMainForm.btnOpenFileClick(Sender: TObject);
begin

  if dlOpenFile.Execute then
  begin
    memSource.Clear;
    memResult.Clear;

    memSource.Lines.LoadFromFile(dlOpenFile.FileName);
  end;
end;

procedure TMainForm.btnStartClick(Sender: TObject);
var
  i, pos, len :integer;
begin
  source:= memSource.Text;

  try
    RegExpr:= TRegExpr.Create;
    //  �������� �����������
    RegExpr.Expression:= '(/\*(.*?)\*/)|(//(.*?)\r)|(/\*\*(.*?)\*/)';
    len:= 0;
    if RegExpr.Exec(source) then
    begin
      repeat
        pos:= RegExpr.MatchPos[0]-len;
        Delete(source,  pos, RegExpr.MatchLen[0]);
        len:= RegExpr.MatchLen[0];
      until not RegExpr.ExecNext;
    end;

    // �������� �������� ������������� #if #else
    RegExpr.Expression:= '(\b#if\b)|(\b#else\b)';
    len:= 0;
    if RegExpr.Exec(source) then
    begin
      repeat
        pos:= RegExpr.MatchPos[0]-len;
        Delete(source,  pos, RegExpr.MatchLen[0]);
        len:= RegExpr.MatchLen[0];
      until not RegExpr.ExecNext;
    end;

    // ����� ��������� ���������
    i:= 0;
    SetLength(const_string_pos, 0);
    SetLength(const_strings, 0);
    RegExpr.Expression:= '"(.*?)"';
    if RegExpr.Exec(source) then
    begin
      repeat
        SetLength(const_string_pos, length(const_string_pos)+1);
        const_string_pos[i][1]:= RegExpr.MatchPos[0];
        const_string_pos[i][2]:= RegExpr.MatchPos[0] + RegExpr.MatchLen[0];
        SetLength(const_strings, length(const_strings)+1);
        const_strings[i]:= RegExpr.Match[0];
        i:= i+1;
      until not RegExpr.ExecNext;
    end;

    arc_count:= 1;    // ���� � �������� �������
    vertex_count:= 2; // ��������� � �������� �������

   // ����� if {} else  {}
    RegExpr.Expression:= '\bif\b(.*)\belse\b(.*)';
    if RegExpr.Exec(source) then
    begin
      repeat
        if not isInRang(RegExpr.MatchPos[0]) then
        begin
          arc_count:= arc_count+5;
          vertex_count:= vertex_count+4;
        end;
      until not RegExpr.ExecNext;
    end;

    //  ����� if ��� else
    RegExpr.Expression:= '\bif\b';
    if RegExpr.Exec(source) then
    begin
      repeat
        if not isInRang(RegExpr.MatchPos[0]) then
        begin
          arc_count:= arc_count+4;
          vertex_count:= vertex_count+3;
        end;
      until not RegExpr.ExecNext;
    end;

    // ����� switch case
    case_count:= 0;
    RegExpr.Expression:= '\bcase\b|\bdefault\b';
    if RegExpr.Exec(source) then
    begin
      repeat
        if not isInRang(RegExpr.MatchPos[0]) then
        begin
          case_count:= case_count+1;
        end;
      until not RegExpr.ExecNext;
    end;
    if case_count<>0 then
    begin
      arc_count:= arc_count + 3 + 2*(case_count-1);
      vertex_count:= vertex_count + 3 + (case_count-1);
    end;

    // ����� ������
    RegExpr.Expression:= '(\bdo\b(.*)\bwhile\b)|(\bfor\b)|(\bwhile\b)';
    if RegExpr.Exec(source) then
    begin
      repeat
        if not isInRang(RegExpr.MatchPos[0]) then
        begin
          arc_count:= arc_count+4;
          vertex_count:= vertex_count+3;
        end;
      until not RegExpr.ExecNext;
    end;

    // ������� ��������� ����������
    max_predicat:= 0;
    predicat_complexity:= 0;
    SubExpr:= TRegExpr.Create;
    RegExpr.Expression:= '\bif\b(\s)*\((.*?)\)\r';
    if RegExpr.Exec(source) then
    begin
      repeat
        if not isInRang(RegExpr.MatchPos[0]) then
        begin
          predicat_str:= RegExpr.Match[0];
          SubExpr.Expression:= '!\b|\|\||&&|`|\^|\|\b|&\b';
          if SubExpr.Exec(predicat_str) then
          repeat
             max_predicat:= max_predicat+1;
          until not SubExpr.ExecNext;
          if max_predicat>predicat_complexity then
            predicat_complexity:= max_predicat;
        end;
      until not RegExpr.ExecNext;
    end;

  {  // ����� goto
    RegExpr.Expression:= '(\bgoto\b)';
    if RegExpr.Exec(source) then
    begin
      repeat
        if not isInRang(RegExpr.MatchPos[0]) then
        begin
          arc_count:= arc_count+1;
          vertex_count:= vertex_count+1;
        end;
      until not RegExpr.ExecNext;
    end;                                 }

  finally
    RegExpr.Free;
  end;

  // ������� ����������� ���������
  program_complexity:= arc_count - vertex_count + 2;

  memResult.Clear;
  memResult.Lines.Add('���������� ��� ����� ���������: '+ IntToStr(arc_count));
  memResult.Lines.Add('���������� ������ ����� ���������: '+ IntToStr(vertex_count));
  memResult.Lines.Add('��������������� ����� ���-�����: '+ IntToStr(program_complexity));
  memResult.Lines.Add('��������� ����������: '+ IntToStr(predicat_complexity));
end;

procedure TMainForm.memSourceChange(Sender: TObject);
begin
  if length(memSource.Text)<>0 then
    btnStart.Enabled:= true
  else
    btnStart.Enabled:= false;
end;

end.
