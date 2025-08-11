package es.ua.dlsi.prog3.p6.reflection.impl;

import es.ua.dlsi.prog3.p6.reflection.IClassAnalyzer;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.HashSet;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;

/**
 * Just findDependantClasses has been included. The other methods have to be done by students. 
 */
public class ClassAnalyzer implements IClassAnalyzer {
	public Class<?> findParentClass(Class<?> c) {
		return c.getSuperclass();
	}
	
	public boolean haveSamePackage(Class<?> c1, Class<?> c2) {
		return (c1.getPackage().equals(c2.getPackage()));
	}
	
	public Set<Class<?>> findAssociatedClasses(Class<?> c) {
		HashSet<Class<?>> attrTypes = new HashSet<>();
		for(Field field : c.getDeclaredFields())
			attrTypes.add(field.getType());
		return attrTypes;
	}
	
    @Override
    public Set<Class<?>> findDependantClasses(Class<?> c) {
        HashSet<Class<?>> result = new HashSet<>();
        for (Method method: c.getDeclaredMethods()) {
            Class<?> returnType = method.getReturnType();
            result.add(returnType);
            for (Class<?> paramType: method.getParameterTypes()) {
                    result.add(paramType);
            }
        }

        for (Constructor<?> method: c.getConstructors()) {
            for (Class<?> paramType : method.getParameterTypes()) {
                result.add(paramType);
            }
        }
        return result;
    }
}
