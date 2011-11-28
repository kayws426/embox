/*
 * generated by Xtext
 */
package org.mybuild.myfile.ui.outline;

import static org.mybuild.myfile.myFile.MyFilePackage.Literals.*;

import org.eclipse.emf.common.util.EList;
import org.eclipse.swt.graphics.Image;
import org.eclipse.xtext.ui.editor.outline.IOutlineNode;
import org.eclipse.xtext.ui.editor.outline.impl.DefaultOutlineTreeProvider;
import org.eclipse.xtext.ui.editor.outline.impl.DocumentRootNode;
import org.mybuild.myfile.myFile.Dependencies;
import org.mybuild.myfile.myFile.Filename;
import org.mybuild.myfile.myFile.Import;
import org.mybuild.myfile.myFile.Model;
import org.mybuild.myfile.myFile.Module;
import org.mybuild.myfile.myFile.Objects;
import org.mybuild.myfile.myFile.Package;
import org.mybuild.myfile.myFile.Sources;

/**
 * customization of the default outline structure
 * 
 */
public class MyFileOutlineTreeProvider extends DefaultOutlineTreeProvider {

	protected void _createChildren(DocumentRootNode parent, Model model) {
		Package pkg = model.getPackage();

		if (pkg != null) {
			createEStructuralFeatureNode(parent, pkg, PACKAGE__NAME,
					labelProvider.getImage(pkg), pkg.getName(), true);
		}

		EList<Import> imports = model.getImports();
		if (!imports.isEmpty()) {
			createEStructuralFeatureNode(parent, model, MODEL__IMPORTS,
					labelProvider.getImage(imports), "import declarations",
					false);
		}

		for (Module module : model.getModules()) {
			createNode(parent, module);
		}
	}

	protected void _createNode(IOutlineNode parent, Import imp) {
		createEStructuralFeatureNode(parent, imp, IMPORT__IMPORTED_NAMESPACE,
				labelProvider.getImage(imp), imp.getImportedNamespace(), true);
	}

	protected void _createNode(IOutlineNode parent, Dependencies dependencies) {
		Image image = labelProvider.getImage(dependencies);

		for (Module module : dependencies.getModules()) {
			String name = module.getName();
			if (name != null) {
				createEStructuralFeatureNode(parent, dependencies,
						DEPENDENCIES__MODULES, image, name, true);
			}
		}
	}

	protected void _createNode(IOutlineNode parent, Sources sources) {
		for (Filename filename : sources.getFiles()) {
			createNode(parent, filename);
		}
	}

	protected void _createNode(IOutlineNode parent, Objects objects) {
		for (Filename filename : objects.getFiles()) {
			createNode(parent, filename);
		}
	}

}
