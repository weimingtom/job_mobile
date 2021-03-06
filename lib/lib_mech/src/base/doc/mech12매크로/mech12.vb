' by icandoit
Imports EnvDTE
Imports System.Diagnostics

Public Module mech12
    Sub jProfile_def()
        DTE.ActiveDocument.Selection.Text = "/* file : " + DTE.ActiveDocument.Name()
        DTE.ActiveDocument.Selection.NewLine()
        DTE.ActiveDocument.Selection.Text = "Coder : by icandoit ( mech12@nate.com)"
        DTE.ActiveDocument.Selection.NewLine()
        DTE.ActiveDocument.Selection.Text = "Date : " + Microsoft.VisualBasic.DateString() + " " + Microsoft.VisualBasic.TimeString
        DTE.ActiveDocument.Selection.NewLine()

        DTE.ActiveDocument.Selection.Text = "comp.: pantavision.co.kr"
        DTE.ActiveDocument.Selection.NewLine()
        DTE.ActiveDocument.Selection.Text = "title : "
        DTE.ActiveDocument.Selection.NewLine()
        DTE.ActiveDocument.Selection.Text = "desc : "
        DTE.ActiveDocument.Selection.NewLine(2)
        DTE.ActiveDocument.Selection.Text = "*/"
        DTE.ActiveDocument.Selection.NewLine(2)
        Dim fileStr As String
        fileStr = DTE.ActiveDocument.Name()
        Dim subString As String
        subString = Microsoft.VisualBasic.Right(fileStr, 2)
        If (subString = ".h") Then
            subString = Microsoft.VisualBasic.Left(fileStr, Len(fileStr) - 2)
            DTE.ActiveDocument.Selection.Text = "#ifndef __" + subString + "_header__"
            DTE.ActiveDocument.Selection.NewLine()
            DTE.ActiveDocument.Selection.Text = "#define __" + subString + "_header__"
            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "#pragma once"
            DTE.ActiveDocument.Selection.NewLine(3)

            DTE.ActiveDocument.Selection.Text = "class " + subString
            DTE.ActiveDocument.Selection.NewLine()
            DTE.ActiveDocument.Selection.Text = "{"
            DTE.ActiveDocument.Selection.NewLine()
            DTE.ActiveDocument.Selection.Text = "public:"
            DTE.ActiveDocument.Selection.NewLine(2)
            DTE.ActiveDocument.Selection.Text = "};"
            DTE.ActiveDocument.Selection.NewLine(4)

            DTE.ActiveDocument.Selection.Text = "#endif // __" + subString + "_header__"
            DTE.ActiveDocument.Selection.NewLine()

        Else
            subString = Microsoft.VisualBasic.Left(fileStr, Len(fileStr) - 4)
            DTE.ActiveDocument.Selection.Text = "#include " + Chr(34) + "stdafx.h" + Chr(34)
            DTE.ActiveDocument.Selection.NewLine()
            DTE.ActiveDocument.Selection.Text = "#include " + Chr(34) + subString + ".h" + Chr(34)
            DTE.ActiveDocument.Selection.NewLine(3)
        End If
    End Sub
    Sub jComment_line()
        DTE.ActiveDocument.Selection.Text = "// *_* by icandoit : " + Microsoft.VisualBasic.DateString() + " " + Microsoft.VisualBasic.TimeString
        DTE.ActiveDocument.Selection.NewLine()
        DTE.ActiveDocument.Selection.Text = "//"
        DTE.ActiveDocument.Selection.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
        DTE.ActiveDocument.Selection.LineDown()
    End Sub

    Sub jComment_multi_begin()
        DTE.ActiveDocument.Selection.Text = "/* *_* by icandoit : " + Microsoft.VisualBasic.DateString() + " " + Microsoft.VisualBasic.TimeString
        DTE.ActiveDocument.Selection.NewLine()
        DTE.ActiveDocument.Selection.LineDown(False, 1)
    End Sub

    Sub jComment_multi_end()
        DTE.ActiveDocument.Selection.Text = "*/ //*_* by icandoit : " + Microsoft.VisualBasic.DateString() + " " + Microsoft.VisualBasic.TimeString
        DTE.ActiveDocument.Selection.NewLine()
        DTE.ActiveDocument.Selection.LineDown(False, 1)
    End Sub

    Sub jFunc_Deco()
        DTE.ActiveDocument.Selection.Text = "//--------------------------------------------------------------------------"
        DTE.ActiveDocument.Selection.NewLine()
        DTE.ActiveDocument.Selection.EndOfLine()
        DTE.ActiveDocument.Selection.NewLine()
        DTE.ActiveDocument.Selection.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
        DTE.ActiveDocument.Selection.Text = "//--------------------------------------------------------------------------"
        DTE.ActiveDocument.Selection.Collapse()
        DTE.ActiveDocument.Selection.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstText)
        DTE.ActiveDocument.Selection.LineDown()
    End Sub


    Function CanToggleToolWindow(ByVal vsWindowKind As String, ByRef ToolWin As Window) As Boolean
        '////////////////////////////////////////////
        'DESCRIPTION: Returns 'True' if given tool windows is open; false otherwise.
        '////////////////////////////////////////////

        Try
            ToolWin = DTE.Windows.Item(vsWindowKind)
        Catch ex As System.IndexOutOfRangeException
            Return False
        Catch ex As System.Exception
            MsgBox(ex.GetType().ToString() & vbNewLine & vbNewLine & ex.Message)
            Return False
        End Try

        Return True
    End Function

    Sub ToggleToolWindow(ByVal vsWindowKind As String, ByRef ShouldToggle As Boolean)
        '////////////////////////////////////////////
        'DESCRIPTION: Toggles a tool window if applicable
        '////////////////////////////////////////////

        Dim ToolWin As Window
        If (Not CanToggleToolWindow(vsWindowKind, ToolWin)) Then
            ' Given tool windows is closed
            ShouldToggle = False
            Exit Sub
        End If
        If (ToolWindowsAreVisible) Then
            ' Toggle will close this window
            If (ToolWin.Visible()) Then
                ' Next time we toggle this window will be re-opened
                ShouldToggle = True
            End If
            ToolWin.Visible = False
        Else
            If (ShouldToggle) Then
                ' Re-open if we closed it
                ToolWin.Visible = True
            End If
        End If
    End Sub

    Sub Toggle_Tool_Windows()
        '////////////////////////////////////////////
        'DESCRIPTION: Closes/Opens tool windows
        '////////////////////////////////////////////

        ' Additional windows (i.e, Server, debug, etc.) can also be added
        'ToggleToolWindow(Constants.vsWindowKindClassView, ClassViewWasOpen)
        'ToggleToolWindow(Constants.vsWindowKindCommandWindow, CommandWindowWasOpen)
        'ToggleToolWindow(Constants.vsWindowKindMacroExplorer, MacroExplorerWasOpen)
        'ToggleToolWindow(Constants.vsWindowKindObjectBrowser, ObjectBrowserWasOpen)
        ToggleToolWindow(Constants.vsWindowKindOutput, OutputWasOpen)
        'ToggleToolWindow(Constants.vsWindowKindProperties, PropertiesWasOpen)
        'ToggleToolWindow(Constants.vsWindowKindSolutionExplorer, SolutionExplorerWasOpen)
        'ToggleToolWindow(Constants.vsWindowKindTaskList, TaskListWasOpen)
        'ToggleToolWindow(Constants.vsWindowKindToolbox, ToolboxWasOpen)

        ToolWindowsAreVisible = (Not ToolWindowsAreVisible)
    End Sub

    ' ToolWindowsAreVisible indicates whether we are opening/closing; 
    ' First time we toggle we are always going to close the windows
    Dim ToolWindowsAreVisible As Boolean = True

    ' These flags indicate whether we will open/close a particular tool window
    Dim ClassViewWasOpen As Boolean
    Dim CommandWindowWasOpen As Boolean
    Dim MacroExplorerWasOpen As Boolean
    Dim ObjectBrowserWasOpen As Boolean
    Dim OutputWasOpen As Boolean
    Dim PropertiesWasOpen As Boolean
    Dim SolutionExplorerWasOpen As Boolean
    Dim TaskListWasOpen As Boolean
    Dim ToolboxWasOpen As Boolean



    ' 구글 서치기능
    ' http://mypage.sarang.net/tt/120

    Public Sub SearchGoogleForSelectedText()
        Dim s As String = ActiveWindowSelection().Trim()
        If s.Length > 0 Then
            DTE.ItemOperations.Navigate("http://www.google.co.kr/search?q=" & s)
            'DTE.ItemOperations.Navigate("http://www.google.co.kr/search?hl=ko&lr=lang_ko&q=site%3Amsdn.microsoft.com+" & s)

        End If
    End Sub

    Private Function ActiveWindowSelection() As String
        If DTE.ActiveWindow.ObjectKind = EnvDTE.Constants.vsWindowKindOutput Then
            Return OutputWindowSelection()
        End If
        Return SelectionText(DTE.ActiveWindow.Selection)
    End Function

    Private Function OutputWindowSelection() As String
        Dim w As Window = DTE.Windows.Item(EnvDTE.Constants.vsWindowKindOutput)
        Dim ow As OutputWindow = w.Object
        Dim owp As OutputWindowPane = ow.OutputWindowPanes.Item(ow.ActivePane.Name)
        Return SelectionText(owp.TextDocument.Selection)
    End Function

    Private Function SelectionText(ByVal sel As EnvDTE.TextSelection) As String
        If sel Is Nothing Then
            Return ""
        End If
        If sel.Text.Length = 0 Then
            SelectWord(sel)
        End If
        If sel.Text.Length <= 2 Then
            Return ""
        End If
        Return sel.Text
    End Function

    Private Sub SelectWord(ByVal sel As EnvDTE.TextSelection)
        Dim leftPos As Integer
        Dim line As Integer
        Dim pt As EnvDTE.EditPoint = sel.ActivePoint.CreateEditPoint()

        sel.WordLeft(True, 1)
        line = sel.TextRanges.Item(1).StartPoint.Line
        leftPos = sel.TextRanges.Item(1).StartPoint.LineCharOffset
        pt.MoveToLineAndOffset(line, leftPos)
        sel.MoveToPoint(pt)
        sel.WordRight(True, 1)
    End Sub




    Public Sub SwitchHeaderSource()
        Dim OldFileName As String
        Dim NewFileName As String
        Dim FileExt As String
        Dim Pos As Integer

        OldFileName = Application.ActiveDocument.FullName

        Pos = InStr(1, OldFileName, ".", CompareMethod.Text)
        If Pos = 0 Then
            Exit Sub
        End If

        FileExt = Right(OldFileName, Len(OldFileName) - Pos)

        If FileExt = "h" Then
            NewFileName = Left(OldFileName, Len(OldFileName) - 2) + ".cpp"
        ElseIf FileExt = "cpp" Then
            NewFileName = Left(OldFileName, Len(OldFileName) - 4) + ".h"
        Else
            Beep()
            Exit Sub
        End If

        Application.DTE.ItemOperations.OpenFile(NewFileName, Constants.vsViewKindCode)
        If (Err.Number <> 0) Then
            MsgBox(Err.Description)
        End If
    End Sub



    Public Sub SearchDicForSelectedText()
        Dim s As String = ActiveWindowSelection().Trim()
        If s.Length > 0 Then
            DTE.ItemOperations.Navigate("http://engdic.daum.net/dicen/small_search_word.do?q=" & s)
        End If
    End Sub

End Module
