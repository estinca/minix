@interface Foo
@property (readonly) id x;
-(int) mymethod;
-(const id) mymethod2:(id)x blah:(Class)y boo:(SEL)z;
-(bycopy)methodIn:(in int)i andOut:(out short *)j , ...;
@end

// RUN: c-index-test -test-print-type %s | FileCheck %s
// CHECK: ObjCPropertyDecl=x:2:25 [readonly,] [type=id] [typekind=ObjCId] [canonicaltype=id] [canonicaltypekind=ObjCObjectPointer] [isPOD=1]
// CHECK: ObjCInstanceMethodDecl=mymethod:3:8 [type=] [typekind=Invalid] [resulttype=int] [resulttypekind=Int] [isPOD=0]
// CHECK: ObjCInstanceMethodDecl=mymethod2:blah:boo::4:13 [type=] [typekind=Invalid] [resulttype=const id] [resulttypekind=ObjCId] [args= [id] [ObjCId] [Class] [ObjCClass] [SEL] [ObjCSel]] [isPOD=0]
// CHECK: ParmDecl=z:4:52 (Definition) [type=SEL] [typekind=ObjCSel] [canonicaltype=SEL *] [canonicaltypekind=Pointer] [isPOD=1]
// CHECK: ObjCInstanceMethodDecl=methodIn:andOut::5:10 (variadic) [Bycopy,] [type=] [typekind=Invalid] [resulttype=id] [resulttypekind=ObjCId] [args= [int] [Int] [short *] [Pointer]] [isPOD=0]
// CHECK: ParmDecl=i:5:27 (Definition) [In,] [type=int] [typekind=Int] [isPOD=1]
// CHECK: ParmDecl=j:5:49 (Definition) [Out,] [type=short *] [typekind=Pointer] [isPOD=1] [pointeetype=short] [pointeekind=Short]
