package Myown;



import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;

import org.objectweb.asm.*;


public class RemoveMethod {
	public static void main(String args[]) throws Exception{
	FileInputStream is = new FileInputStream(args[0]);

    ClassReader cr = new ClassReader(is);
    ClassWriter cw = new ClassWriter(ClassWriter.COMPUTE_FRAMES);
    ClassVisitor cv = new RemoveMethodAdapter(cw, args[2], null);
    cr.accept(cv, 0);

    FileOutputStream fos = new FileOutputStream(args[1]);
    fos.write(cw.toByteArray());
    fos.close();
	}
}

