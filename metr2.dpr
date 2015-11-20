program metr2;

uses
  Vcl.Forms,
  MainUnit in 'MainUnit.pas' {MainForm},
  RegExpr in 'RegExpr.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
