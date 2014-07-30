VERSION 5.00
Object = "{F3A76D0B-AB61-491C-961F-267D38A20250}#1.0#0"; "GainerX.ocx"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3915
   ClientLeft      =   120
   ClientTop       =   435
   ClientWidth     =   5880
   LinkTopic       =   "Form1"
   ScaleHeight     =   3915
   ScaleWidth      =   5880
   StartUpPosition =   3  'Windows ‚ÌŠù’è’l
   Begin VB.CommandButton Command7 
      Caption         =   "dout"
      Height          =   375
      Left            =   1920
      TabIndex        =   13
      Top             =   3360
      Width           =   855
   End
   Begin VB.CheckBox D3 
      Caption         =   "d3"
      Height          =   255
      Left            =   1440
      TabIndex        =   12
      Top             =   3360
      Width           =   375
   End
   Begin VB.CheckBox D2 
      Caption         =   "d2"
      Height          =   300
      Left            =   1080
      TabIndex        =   11
      Top             =   3360
      Width           =   375
   End
   Begin VB.CheckBox D1 
      Caption         =   "d1"
      Height          =   255
      Left            =   720
      TabIndex        =   10
      Top             =   3360
      Width           =   255
   End
   Begin VB.CheckBox D0 
      Caption         =   "d0"
      Height          =   255
      Left            =   360
      TabIndex        =   9
      Top             =   3360
      Width           =   255
   End
   Begin VB.CommandButton Command6 
      Caption         =   "aread"
      Height          =   495
      Left            =   4440
      TabIndex        =   8
      Top             =   2400
      Width           =   975
   End
   Begin VB.CommandButton Command5 
      Caption         =   "AREAD"
      Height          =   495
      Left            =   3000
      TabIndex        =   7
      Top             =   2400
      Width           =   975
   End
   Begin VB.CommandButton Command4 
      Caption         =   "DREAD"
      Height          =   375
      Left            =   1680
      TabIndex        =   6
      Top             =   2520
      Width           =   975
   End
   Begin VB.CheckBox Check1 
      Caption         =   "LED"
      Height          =   375
      Left            =   3360
      TabIndex        =   5
      Top             =   1800
      Width           =   855
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Init"
      Height          =   375
      Left            =   360
      TabIndex        =   3
      Top             =   2520
      Width           =   975
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Close"
      Height          =   495
      Left            =   1680
      TabIndex        =   2
      Top             =   1800
      Width           =   975
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Open"
      Height          =   495
      Left            =   360
      TabIndex        =   1
      Top             =   1800
      Width           =   975
   End
   Begin GainerXLibCtl.Gainer Gainer1 
      Height          =   495
      Left            =   720
      TabIndex        =   0
      Top             =   480
      Visible         =   0   'False
      Width           =   615
      _cx             =   1085
      _cy             =   873
      Enabled         =   -1  'True
      Valid           =   -1  'True
      Object.Visible         =   0   'False
   End
   Begin VB.Label Label1 
      Caption         =   "Label1"
      Height          =   495
      Left            =   2760
      TabIndex        =   4
      Top             =   360
      Width           =   1455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Check1_Click()
    If Check1.Value = 0 Then
        Gainer1.LED = False
    Else
        Gainer1.LED = True
    End If
End Sub

Private Sub Command1_Click()
    Gainer1.Open "COM3"
End Sub

Private Sub Command2_Click()
    Gainer1.Close
End Sub

Private Sub Command3_Click()
    Gainer1.Configuration = DEFAULT_MODE
End Sub


Private Sub Command4_Click()
    Gainer1.ReadAllDigitalInputs True
End Sub

Private Sub Command5_Click()
    Gainer1.ReadAllAnalogInputs True
End Sub

Private Sub Command6_Click()
    Dim b() As Byte
    Dim i As Integer
    Dim s As String
    b = Gainer1.ReadAllAnalogInputs(False)
    For i = 0 To UBound(b)
        s = s & b(i) & "-"
    Next i
    MsgBox s
End Sub

Private Sub Command7_Click()
    Dim b(3) As Byte
    b(0) = D0.Value
    b(1) = D1.Value
    b(2) = D2.Value
    b(3) = D3.Value
    Gainer1.WriteAllDigitalOutputs b
End Sub

Private Sub Gainer1_AnalogInputs(NewValue() As Byte)
    Dim s As String
    Dim i As Integer
    For i = 0 To UBound(NewValue)
        s = s & NewValue(i) & "-"
    Next i
    Label1.Caption = s
End Sub

Private Sub Gainer1_ButtonPressed()
    Label1.Caption = "button pressed"
End Sub

Private Sub Gainer1_ButtonReleased()
    Label1.Caption = "button released"
End Sub

Private Sub Gainer1_DigitalInputs(NewValue() As Byte)
    Dim s As String
    Dim i As Integer
    s = UBound(NewValue) & ":"
    For i = 0 To UBound(NewValue)
        s = s & NewValue(i) & "-"
    Next i
    Label1.Caption = s
End Sub

Private Sub Gainer1_Error(ByVal Code As Long)
    MsgBox "Error:" & Code
End Sub
