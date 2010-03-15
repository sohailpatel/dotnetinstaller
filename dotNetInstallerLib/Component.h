#pragma once

#include "DownloadDialog.h"
#include "EmbedFile.h"
#include "EmbedFolder.h"
#include "InstalledCheck.h"

enum component_type
{
	component_type_undefined = 0, 
	component_type_cmd, // shell command
	component_type_msi, // windows installer setup
	component_type_msu, // windows update
	component_type_msp, // windows installer patch
	component_type_openfile // ShellExecute call to open a file
};

class Component
{
public:
    Component(component_type t);
    virtual ~Component();
public:
	// component display name
	XmlAttribute display_name;
	// component type: cmd, msi, openfile
	component_type type;
	// component id
	XmlAttribute id;
	// component uninstall display name
	XmlAttribute uninstall_display_name;
	// component status when installed
	XmlAttribute status_installed;
	// component status when not installed
	XmlAttribute status_notinstalled;
	// filtro che indica il minimo sistema operativo in cui lanciare il componente (estremo escluso)
	XmlAttribute os_filter_greater;
	// filtro che indica il massimo sistema operativo in cui lanciare il componente (estremo escluso)
	XmlAttribute os_filter_smaller;
	// filtro che indica il filtro per lingua del sistema operativo (es. Italy = 1040, English - United Kingdom = 2057, English - United States = 1033)
	XmlAttribute os_filter_lcid;
	// testo da visualizzare a fine installazione (se vuoto non visualizza niente)
	XmlAttribute installcompletemessage;
	// successful uninstall message
	XmlAttribute uninstallcompletemessage;
	// true per forzare il reboot al termine dell'installazione altrimenti false
	bool mustreboot;
    // message for a reboot after this component
    XmlAttribute reboot_required;
    // true to force a reboot when required
    bool must_reboot_required;
    // message to display on error
    XmlAttribute failed_exec_command_continue;
    // allow to continue setup on error
    bool allow_continue_on_error;
	// filter for processor architecture
	XmlAttribute processor_architecture_filter;
    // cancelled by user
    bool cancelled;
    // true if component is required for final command to execute
    bool required;
	// true if component is selected by default
    bool selected;
	// classi per gestire la verifica se il componente � installato o no
	std::vector<InstalledCheckPtr> installedchecks;
	// informazioni sull'eventuale download dei componenti (fa riferimento al nodo downloaddialog all'interno di Component, se non � presente non viene scaricato nessun componente)
	DownloadDialogPtr downloaddialog;
	// embedded files
	std::vector< EmbedFilePtr > embedfiles;
	// embedded folders
	std::vector< EmbedFolderPtr > embedfolders;
	// supports install
	bool supports_install;
	// supports uninstall
	bool supports_uninstall;
	// funzione virtuale specifica per il tipo di componente
	virtual void Exec() = 0;
	virtual void Wait(DWORD tt = 1000);
	virtual bool IsRebootRequired() const;
	virtual bool IsExecuting() const = 0;
	virtual bool IsInstalled() const;
	// indica se il componente verr� eseguito o no
	bool checked;
	// load a component from an xml node
	virtual void Load(TiXmlElement * node);
	// returns true if this component is supported on this operating system/lcid
	virtual bool IsSupported(LCID lcid) const;
	virtual int GetExitCode() const = 0;
	virtual std::wstring GetString(int indent = 0) const;
	std::wstring GetAdditionalCmd() const;
	std::wstring GetDisplayName() const;
};

typedef shared_any<Component *, close_delete> ComponentPtr;
